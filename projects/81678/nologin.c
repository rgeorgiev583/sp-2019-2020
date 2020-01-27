#include <stdio.h>
#include <stdlib.h>
#define REQUIRED_ARGS_NUMBER 0

int main(int argc, const char *const *argv){
  if(argc > REQUIRED_ARGS_NUMBER + 1){
    exit(1);
  }
  FILE *file = fopen("/etc/nologin.txt", "r");
  if(file == NULL){
    puts("The account is currently unavailable");
    exit(1);
  }
  char read;
  while((read = getc(file)) != EOF){
    putchar(read);
  }
  exit(1);
}
