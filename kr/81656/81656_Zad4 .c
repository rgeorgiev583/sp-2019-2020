#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
int pipe_sort_uniq_fileno[2];
    if (-1 == pipe(pipe_sort_uniq_fileno))
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t sort_pid = fork();
    switch (sort_pid)
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);

    case 0:
        close(pipe_sort_uniq_fileno[0]);
        dup2(pipe_sort_uniq_fileno[1], STDOUT_FILENO);

         
        argv[0]="sort";
        if (-1 == execvp("sort", argv+1))
        {
            perror("exec");
            exit(EXIT_FAILURE);
        }
    }
    pid_t uniq_pid=fork(); 
    switch (uniq_pid)
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);

    case 0:
       dup2(pipe_sort_uniq_fileno[0], STDIN_FILENO);
       close(pipe_sort_uniq_fileno[1]);

    if (-1 == execlp("uniq", "uniq", NULL))
        {
            perror("exec");
            exit(EXIT_FAILURE);
        }
    }

    close(pipe_sort_uniq_fileno[0]);
    close(pipe_sort_uniq_fileno[1]);

    waitpid(sort_pid, NULL, 0);

     int status;
    waitpid(uniq_pid, &status, 0);
    return WEXITSTATUS(status);
}    
























 