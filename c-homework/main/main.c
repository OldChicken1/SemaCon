#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <db.h>

#define INPUT_LIMIT 50
#define BASE 10
#define INSERT 0
#define FIND 1
#define DELETE 2

int main()
{
  char command[INPUT_LIMIT];
  char *db_commands[3] = {"insert", "find", "delete"};
  while (1)
  {
    printf("Enter command: ");
    scanf("%[^\n]%*c", command);
    char delim[] = " ";
    char *fileName;
    int db_command = -1;
    uint64_t id;
    int counter = 0;
    char *ptr = strtok(command, delim);
    int isError = 0;
    while (ptr != NULL)
    {
      printf("'%s'\n", ptr);
      if (counter == 0)
      {
        if (strcmp(ptr, "dbcli") != 0)
        {
          printf("Error: invalid command\n");
          isError = 1;
        }
      }
      if (counter == 1)
      {
        fileName = ptr;
      }
      if (counter == 2)
      {
        int i;
        for (i = 0; i < 3; i++)
        {
          if (strcmp(ptr, db_commands[i]) == 0)
          {
            db_command = i;
          }
        }
        if (db_command == -1)
        {
          printf("Error: invalid command\n");
          isError = 1;
        }
      }
      if (counter == 3)
      {
        char *endPtr;
        id = strtoull(ptr, &endPtr, BASE);
        if (*endPtr)
          printf("Unable to convert '%s' to base %d.", ptr, BASE);
        if (id == -1)
        {
          printf("Error: invalid id, too big\n");
          isError = 1;
        }
      }
      ptr = strtok(NULL, delim);
      counter++;
      if (isError)
      {
        break;
      }
    }
    if (counter != 4)
    {
      printf("Error: invalid command, 4 parameters are required to enter\n");
      continue;
    }
    if (!isError)
    {
      db_t *db = db_new();
      db_open(db, fileName);
      if (db_command == INSERT)
      {
        db_insert(db, id);
      }
      else if (db_command == FIND)
      {
        db_find(db, id);
      }
      else if (db_command == DELETE)
      {
        db_delete(db, id);
      }
      db_free(db);
    }
    isError = 0;
  }

  return 0;
}
