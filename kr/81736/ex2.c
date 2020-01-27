#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define REQ_ARG 4

int main(int argc, const char* const* argv){
     if(argc < REQ_ARG) exit(EXIT_FAILURE);
     
     int file1 = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0640);
     int file2 = open(argv[4], O_RDONLY);

     dup2(file1, STDOUT_FILENO);
     dup2(file2, STDIN_FILENO);

     execlp("tr", "tr", argv[1], argv[2], NULL);
}
