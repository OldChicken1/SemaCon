#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>


#include "db.h"

#define FILENAME_SIZE  50
#define READ_SIZE      20
#define HASHTABLE_SIZE 200
#define INPUT_ID_BASE  10
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
  // uint64_t* hashArray;
};



int hash(uint64_t key){
  return key % HASHTABLE_SIZE;
}

db_t * db_new()
{
  db_t* db = (db_t*) (malloc(sizeof(db_t)));
  // db->hashArray = malloc(sizeof(struct dataItem*)*HASHTABLE_SIZE);
  // db->hashArray = malloc(sizeof(uint64_t)*HASHTABLE_SIZE);
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
    printf("no such file exist.\n");
    return EEXIST;
  }
  while(fscanf(db->fp, "%s\n", str) != EOF){
    printf("wtf");
    printf("inside open loop, str:%s\n", str);
    char* endPtr;
    uint64_t aKey = strtoull(str, &endPtr, INPUT_ID_BASE);
    if(*endPtr)
      printf("Unable to convert '%s' to base %d.",str, INPUT_ID_BASE);
    printf("key value stored: %" PRIu64 "\n", aKey);
    int index = hash(aKey);
    while(db->hashArray[index].isStore!=-1){
      index++;
      index = hash(index);
    }
    // struct dataItem* item = (struct dataItem*)malloc(sizeof(struct dataItem));
    // uint64_t key = aKey;
    // item->key = aKey;
    db->hashArray[index].key = aKey;
    db->hashArray[index].isStore = 1;
    db->count++;
  }
  return 0;
}

int db_insert(db_t* db, uint64_t id)
{
  printf("inside insert, filename: %s\n", db->fileName);
  db->fp = fopen(db->fileName, "a");
  // struct dataItem* item = (struct dataItem*)malloc(sizeof(struct dataItem));
  // item->key = id;
  // uint64_t key = id;
  // struct dataItem* item;
  // item->key = id;
  printf("hash0: %d, hash1: %d, 2: %ld, 3: %ld\n", db->hashArray[0].isStore,
          db->hashArray[1].isStore, db->hashArray[2].key, db->hashArray[3].key);
  int index = hash(id);
  printf("index: %d\n", index);
  while(db->hashArray[index].isStore==1){
    printf("inside probe\n");
    printf("hash key is : %ld\n", db->hashArray[index].key);
    if(db->hashArray[index].key == id){
      printf("ID already exists\n");
      return EEXIST;
    }
    index++;
    index = hash(index);
  }
  db->hashArray[index].key = id;
  db->hashArray[index].isStore = 1;
  fprintf(db->fp, "%ld\n", id);
  fclose(db->fp);
  return 0;
}

int db_find(db_t* db, uint64_t id)
{
  if(access(db->fileName, F_OK) != 0){
    printf("Error: Invalid filename.%d\n", errno);
    return errno;

  }
  int index = hash(id);
  while(db->hashArray[index].isStore!=-1){
    if(db->hashArray[index].key == id){
      return 1; //id found
    }
    index++;
    index = hash(index);
  }
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
    // FILE* temp = fopen("temp.txt")
    db->fp = fopen(db->fileName, "w+");
    int i;
    for(i = 0; i < HASHTABLE_SIZE; i++){
      if(db->hashArray[i].isStore == 1){
        printf("value %ld is stored at %d\n", db->hashArray[i].key, i);
        fprintf(db->fp, "%ld\n", db->hashArray[i].key);
      }
    }
    fclose(db->fp);
    return 1;
  }
  
  return 0; //not found;
}

void db_free(db_t* db)
{
  // int i;
  // for(i = 0; i < HASHTABLE_SIZE; i++){
  //   if(db->hashArray[i] != NULL){
  //     printf("hashArray value:%ld\n", db->hashArray[i]->key);
  //     free(db->hashArray[i]);
  //   }
  // }
  // free(db->hashArray); 
  free(db);
  // printf("after freed:%ld\n", item->key);
}
