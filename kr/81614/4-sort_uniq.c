#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc,char*argv[])
{

    int pipe_fd[2];
    pipe(pipe_fd);

    pid_t sort_pid = fork()
    if(sort_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(sort_pid == 0)
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1],STDOUT_FILENO);
        argv[0] = "sort";
        execv("sort","sort",argv);
    }

    pid_t uniq_pid = fork();
    if(uniq_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(uniq_pid == 0)
    {
        dup2(pipe_fd[0],STDIN_FILENO);
        close(pipe_fd[1]);
        execlp("uniq","uniq",NULL);
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(sort_pid,NULL,0);
    int status;
    waitpid(uniq_pid,&status,0);

    exit(status);
}
