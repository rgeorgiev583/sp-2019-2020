#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static void iFlagFunction(int input_fileno, int spacing){
  char buffer;
  ssize_t read_result;
  if(-1 == lseek(input_fileno,-2,SEEK_CUR)){
    perror("lseek");
    exit(EXIT_FAILURE);
  }
  read_result = read(input_fileno, &buffer, 1);
  if(-1 == read_result){
    perror("read");
    exit(EXIT_FAILURE);
   }

  if('\n' == buffer || '\r' == buffer || '\t' == buffer  || ' ' == buffer){
       for (int i = 0; i < spacing; i++){
          if (-1 == write(STDOUT_FILENO, " ", 1))
           {
           perror("write");
           exit(EXIT_FAILURE);
          }
        }
        if(-1 == lseek(input_fileno,1,SEEK_CUR)){
    perror("lseek");
    exit(EXIT_FAILURE);
  }
  }
  else
  {
     read_result = read(input_fileno, &buffer, 1);
  if(-1 == read_result){
    perror("read");
    exit(EXIT_FAILURE);
   }
    
    if (-1 == write(STDOUT_FILENO, &buffer, 1))
      {
        perror("write");
        exit(EXIT_FAILURE);
       }
  }
}


static void expand(int input_fileno, bool iFlag, int spacing)
{
    char buffer;
    ssize_t read_result;
    while ((read_result = read(input_fileno, &buffer, 1)) != 0)
    {
        if (-1 == read_result)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if ('\t' == buffer)
        {
          if(iFlag){
            iFlagFunction(input_fileno,spacing);

          }
          else{
            for (int i = 0; i < spacing; i++)
                if (-1 == write(STDOUT_FILENO, " ", 1))
                {
                    perror("write");
                    exit(EXIT_FAILURE);
                }
          }
        }
        else
        {
            if (-1 == write(STDOUT_FILENO, &buffer, 1))
            {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }
    }
}

int main(int argc, const char *const *argv)
{
  int optionsNumber = 0;
  bool iFlag = false;
  int spacing = 8;

    if (argc > 1)
    {
      if(argv[1][0] == '-' && argv[1][1]=='i' || argc>2 && argv[2][0] == '-' && argv[2][1]=='i'){
        iFlag = true;
        optionsNumber++; 
        }
      if(argv[1][0] == '-' && argv[1][1] == 't'){
        optionsNumber++;
        spacing = atoi(&argv[1][2]);
      }
      if(argc> 2 && argv[2][0] == '-' && argv[2][1] == 't'){
        optionsNumber++;
        spacing = atoi(&argv[2][2]);
      }

      if(optionsNumber == 2 && argc == 3 || optionsNumber == 1 && argc == 2){
        expand(STDIN_FILENO,iFlag,spacing);
      }
      else{
        for (int i = optionsNumber +1; i < argc; i++)
        {
            int input_fileno = open(argv[i], O_RDONLY);
            if (-1 == input_fileno)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }

            expand(input_fileno,iFlag,spacing);
        }
      }
    }
    else
        expand(STDIN_FILENO,iFlag,spacing);

    return EXIT_SUCCESS;
}