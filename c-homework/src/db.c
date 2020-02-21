#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>


#include "db.h"

#define FILENAME_SIZE  50
#define READ_SIZE      20
#define HASHTABLE_SIZE 200 //can be changed to much larger
#define INPUT_ID_BASE  10

// a simple hash table for storing id
struct dataItem{
  uint64_t key;
  int data;
  int isStore;
}; 

struct db{
  FILE *fp;
  const char *fileName;
  int count;
  struct dataItem hashArray[HASHTABLE_SIZE];
};


//a simple hash method
int hash(uint64_t key){
  return key % HASHTABLE_SIZE;
}

db_t * db_new()
{
  db_t* db = (db_t*) (malloc(sizeof(db_t)));
  int i;
  for(i = 0; i < HASHTABLE_SIZE; i++){
    db->hashArray[i].isStore = -1;
  }
  db->count = 0;
  return db;
}

int db_open(db_t* db, const char* filename)
{
  db->fp = fopen(filename, "r");
  db->count = 0;
  db->fileName = filename;
  char str[READ_SIZE];
  if(db->fp == NULL){
    printf("No such file exist.\n");
    return EEXIST;
  }
  while(fscanf(db->fp, "%s\n", str) != EOF){
    char* endPtr;
    uint64_t aKey = strtoull(str, &endPtr, INPUT_ID_BASE);
    if(*endPtr)
      printf("Unable to convert '%s' to base %d.",str, INPUT_ID_BASE);
    int index = hash(aKey);
    while(db->hashArray[index].isStore!=-1){
      index++;
      index = hash(index);
    }
    db->hashArray[index].key = aKey;
    db->hashArray[index].isStore = 1;
    db->count++;
  }
  return 0;
}

int db_insert(db_t* db, uint64_t id)
{
  if(db->count > HASHTABLE_SIZE){
    printf("Out of memory. Increase the hashtable size for more data.\n");
    return ENOMEM;
  }
  if(access(db->fileName, F_OK) != 0){
    printf("Creating a new database.\n");
  }
  db->fp = fopen(db->fileName, "a");
  int index = hash(id);
  while(db->hashArray[index].isStore==1){
    if(db->hashArray[index].key == id){
      printf("ID already exists\n");
      return EEXIST;
    }
    index++;
    index = hash(index);
  }
  db->hashArray[index].key = id;
  db->hashArray[index].isStore = 1;
  db->count++;
  fprintf(db->fp, "%ld\n", id);
  fclose(db->fp);
  printf("Insert successfully.\n");
  return 0;
}

int db_find(db_t* db, uint64_t id)
{
  int index = hash(id);
  while(db->hashArray[index].isStore!=-1){
    if(db->hashArray[index].key == id){
      printf("ID is found.\n");
      return 1; //id found
    }
    index++;
    index = hash(index);
  }
  printf("ID is not found in the database.\n");
  return 0; //not found;

}


int db_delete(db_t* db, uint64_t id)
{
  int isDeleted = 0;
  int index = hash(id);
  while(db->hashArray[index].isStore!=-1){
    if(db->hashArray[index].key == id){
      db->hashArray[index].isStore = 0;
      isDeleted = 1; //id found and deleted
      break;
    }
    index++;
    index = hash(index);
  }
  if(isDeleted == 1){
    db->fp = fopen(db->fileName, "w+");
    int i;
    for(i = 0; i < HASHTABLE_SIZE; i++){
      if(db->hashArray[i].isStore == 1){
        fprintf(db->fp, "%ld\n", db->hashArray[i].key);
      }
    }
    db->count--;
    fclose(db->fp);
    printf("ID is deleted\n");
    return 1;
  }
  printf("Deletion failed, ID is not found in the database.\n");
  return 0; //not found;
}

void db_free(db_t* db)
{
  free(db);
}
