#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int pipe_fileno[2];
    if (-1 == pipe(pipe_fileno))
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t grep_pid = fork();
    switch (grep_pid)
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);

    case 0:
        if (-1 == close(pipe_fileno[0]))
        {
            perror("close");
            exit(EXIT_FAILURE);
        }

        if (-1 == dup2(pipe_fileno[1], STDOUT_FILENO))
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }

        argv[1] = "grep";
        if (-1 == execvp("grep", argv + 1))
        {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }

    pid_t head_pid = fork();
    switch (head_pid)
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);

    case 0:
        if (-1 == dup2(pipe_fileno[0], STDIN_FILENO))
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }

        if (-1 == close(pipe_fileno[1]))
        {
            perror("close");
            exit(EXIT_FAILURE);
        }

        if (-1 == execlp("head", "head", "-n", argv[1], NULL))
        {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    }

    if (-1 == close(pipe_fileno[0]))
    {
        perror("close");
        exit(EXIT_FAILURE);
    }

    if (-1 == close(pipe_fileno[1]))
    {
        perror("close");
        exit(EXIT_FAILURE);
    }

    if (-1 == waitpid(grep_pid, NULL, 0))
    {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }

    int status;
    if (-1 == waitpid(head_pid, &status, 0))
    {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }

    return WEXITSTATUS(status);
}