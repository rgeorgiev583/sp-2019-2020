#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#define REQUIRED_ARG_COUNT 2

int main(int argc, char **argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    int pipe_head_grep_fileno[2];
    if (-1 == pipe(pipe_head_grep_fileno))
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t head_pid = fork();
    switch (head_pid)
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);

    case 0:
        close(pipe_head_grep_fileno[0]);
        dup2(pipe_head_grep_fileno[1], STDOUT_FILENO);

        argv[0] = "head";
        argv[2] = argv[1];
        argv[1] = "-n";
        if (-1 == execvp("head", argv))
        {
            perror("exec");
            exit(EXIT_FAILURE);
        }
    }

    int pipe_grep_wc_fileno[2];
    if (-1 == pipe(pipe_grep_wc_fileno))
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
        dup2(pipe_head_grep_fileno[0], STDIN_FILENO);
        close(pipe_head_grep_fileno[1]);
        close(pipe_grep_wc_fileno[0]);
        dup2(pipe_grep_wc_fileno[1], STDOUT_FILENO);

        if (-1 == execlp("grep", "grep", argv[2], NULL))
        {
            perror("exec");
            exit(EXIT_FAILURE);
        }
    }

    pid_t wc_pid = fork();
    switch (wc_pid)
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);

    case 0:
        close(pipe_head_grep_fileno[0]);
        close(pipe_head_grep_fileno[1]);
        dup2(pipe_grep_wc_fileno[0], STDIN_FILENO);
        close(pipe_grep_wc_fileno[1]);

        if (-1 == execlp("wc", "wc", "-l", NULL))
        {
            perror("exec");
            exit(EXIT_FAILURE);
        }
    }

    close(pipe_head_grep_fileno[0]);
    close(pipe_head_grep_fileno[1]);
    close(pipe_grep_wc_fileno[0]);
    close(pipe_grep_wc_fileno[1]);

    waitpid(head_pid, NULL, 0);
    waitpid(grep_pid, NULL, 0);

    int status;
    waitpid(wc_pid, &status, 0);
    return WEXITSTATUS(status);
}