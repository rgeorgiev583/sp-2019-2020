#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int pipe_fileno[2];
    if (-1 == pipe(pipe_fileno))
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t who_pid = fork();
    switch (who_pid)
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);

    case 0:
        close(pipe_fileno[0]);
        dup2(pipe_fileno[1], STDOUT_FILENO);

        if (-1 == execlp("who", "who", NULL))
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
        dup2(pipe_fileno[0], STDIN_FILENO);
        close(pipe_fileno[1]);

        if (-1 == execlp("wc", "wc", "-l", NULL))
        {
            perror("exec");
            exit(EXIT_FAILURE);
        }
    }

    close(pipe_fileno[0]);
    close(pipe_fileno[1]);

    waitpid(who_pid, NULL, 0);

    int status;
    waitpid(wc_pid, &status, 0);
    return WEXITSTATUS(status);
}