#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MIN_ARGUMENT_COUNT 2
#define BUFF_SIZE 128

int main(int argc, const char* const* argv){
  if(argc < MIN_ARGUMENT_COUNT){
    exit(EXIT_FAILURE);
  }
  
  char proc[8] = "/proc/";
  char cwd[8] = "/cwd";
  int i;
  for (i = 1; i < argc; i++){
    char loc[BUFF_SIZE] = "";
    strcat(loc, proc);
    strcat(loc, argv[i]);
    strcat(loc, cwd);
    
    char dir[BUFF_SIZE] = "";
    int sizeRead = readlink(loc, dir, BUFF_SIZE);   

    char message[BUFF_SIZE] = "";
    strcat(message, argv[i]);
    strcat(message, ": ");
    strcat(message, dir);
    strcat(message, "\n");

    write(STDOUT_FILENO, message, strlen(message));
   
  }

  exit(0);
}
