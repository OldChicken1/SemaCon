#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#define INPUT_LIMIT 50

int isFileExist(const char* filename);
int main()
{
//  char command[] = "Hello my name is Jay";
  char command[INPUT_LIMIT];
  printf("Enter command: ");
  scanf("%[^\n]%*c", command);
  char delim[] = " ";
  int counter = 0;
  char *ptr = strtok(command, delim);
  while(ptr != NULL){
    printf("'%s'\n", ptr);
    if(counter == 0){
      if(strcmp(ptr, "dbcli")!=0){
        printf("Error: invalid command\n");
      }
    }
    if(counter == 1){
      if(!isFileExist(ptr)){
        printf("Error: invalid command\n");
      }
    }
    ptr = strtok(NULL, delim);
    counter++;
  }
  if(counter != 4){
    printf("Error: invalid command, counter: %d\n", counter);
  
  }
  return 0;
}

int isFileExist(const char* filename){
  struct stat buf;
  int exist = stat(filename, &buf);
  if(exist==0){
    printf("file exist\n");
    return 1;
  } 
  else return 0;

}
