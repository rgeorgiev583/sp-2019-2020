#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include <fcntl.h>
#include <err.h>
#include <sys/wait.h>

int main(int argc, char**argv) {
  int pipe_fd[2];
  
  pipe(pipe_fd);

  pid_t child_pid = fork();

  if (child_pid == 0) {
    dup2(pipe_fd[0], 0);
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    execlp("xargs", "xargs", "kill", NULL);  

  } else {
    dup2(pipe_fd[1], 1);
    close(pipe_fd[1]);
    close(pipe_fd[0]);

    argv[0] = "pidof";
    execvp("pidof", argv);
  }

  exit(EXIT_SUCCESS);
}
