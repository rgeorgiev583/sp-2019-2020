#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int length(const char* word){
  
  int index = 0;

  while(word[index] != '\0'){
    index++;
  }
  return index;
}

void printWord(const char* word){
  if(-1 == write(STDOUT_FILENO, word, length(word))){
    perror("write");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, const char *const *argv) {
  //without arguments
  if(argc == 1){
    while(true){
      printWord("y\n");
    }
  }
  //with arguments
  else if(argc >= 1){
   
    while(true){

      //print first word
      printWord(argv[1]);

      //print other words 
      int index = 2;
      while(index < argc){
        printWord(" ");	    
        printWord(argv[index]);
	index++;
      }

      //print new line
      printWord("\n");
    }
  }
}
