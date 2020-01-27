#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static void helperFunction(int input_fileno,int spacing){
  int holes = 0;
  char bufhole[BUFSIZ];

      size_t read_result = read(input_fileno,&bufhole,spacing);
      if(-1 == read_result){
        perror("read");
        exit(EXIT_FAILURE);
      }   

      int i=0;
      while (i<spacing)
      {
        if(bufhole[i] == ' '){
          holes++;
        }
        i++;
      }

      if(holes == spacing){
        if(-1 == write(STDOUT_FILENO, "\t",1)){
          perror("write");
          exit(EXIT_FAILURE);
       }
      }
      else{
        if(-1 == write(STDOUT_FILENO, &bufhole,spacing)){
          perror("write");
          exit(EXIT_FAILURE);
        }
      }
}

static void unexpand(int input_fileno,bool aOptionFlag,int spacing){
  char buffer;
  ssize_t read_result;
  while((read_result = read(input_fileno, &buffer,1)) != 0){
    if(-1 == read_result){
      perror("read");
      exit(EXIT_FAILURE);
    }

  if(!aOptionFlag){
    if('\n' == buffer || '\r' == buffer || '\t' == buffer || ' ' == buffer){

      if(-1 == write(STDOUT_FILENO,&buffer,1)){
        perror("write");
        exit(EXIT_FAILURE);
      }

      helperFunction(input_fileno,spacing);
      
    }
    else{
      if(-1 == write(STDOUT_FILENO,&buffer,1)){
          perror("write");
          exit(EXIT_FAILURE);
        }
      }
    }
  else{
    if(' ' == buffer){
      if(-1 == lseek(input_fileno,-1,SEEK_CUR)){
        perror("lseek");
        exit(EXIT_FAILURE);
      }
      helperFunction(input_fileno,spacing);
    }
    else{
      if(-1 == write(STDOUT_FILENO,&buffer,1)){
          perror("write");
          exit(EXIT_FAILURE);
        }
    }
  }
}
}

int main(int argc, const char* const *argv){
  bool aFlagOption = false;
  bool tFlagOption = false;
  int spacing = 8;
  int optionsNumber = 0;
  if (argc > 1)
    {
      if(argv[1][0] == '-' && argv[1][1]=='a' || argc>2 && argv[2][0] == '-' && argv[2][1]=='a'){
        aFlagOption = true;
        optionsNumber++; 
        }
      if(argv[1][0] == '-' && argv[1][1] == 't'){
        optionsNumber++;
        tFlagOption = true;
        spacing = atoi(&argv[1][2]);
      }
      if(argc> 2 && argv[2][0] == '-' && argv[2][1] == 't'){
        optionsNumber++;
        tFlagOption = true;
        spacing = atoi(&argv[2][2]);
      }

      if(argc == 3 && optionsNumber == 2 || argc == 2 && optionsNumber == 1){
        unexpand(STDIN_FILENO,aFlagOption,spacing);
      }
      else{
        for (int i = optionsNumber+1; i < argc; i++)
        {
            int input_fileno = open(argv[i], O_RDONLY);
            if (-1 == input_fileno)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }

            unexpand(input_fileno,aFlagOption,spacing);
        }
      }
    }
    else
        unexpand(STDIN_FILENO,aFlagOption,spacing);

    return EXIT_SUCCESS;
}
