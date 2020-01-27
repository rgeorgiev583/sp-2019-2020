#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char* argv[]){

  int fd[2];
  pipe(fd);

  int sort = fork();
  if(sort == 0){
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    argv[0] = "sort";
    execvp("sort", argv);
  }
  
  int uniq = fork();
  if(uniq == 0){
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    execlp("uniq", "uniq", NULL);
  }

  waitpid(sort, NULL, 0);
  int status;
  waitpid(uniq, &status, 0);

  exit(status);

}
