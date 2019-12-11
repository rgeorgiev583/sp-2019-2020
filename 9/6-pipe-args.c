#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_ARG_COUNT 100

int main(int argc, const char **argv)
{
    int pipe_fileno[MAX_ARG_COUNT][2];
    pid_t pid[MAX_ARG_COUNT];

    for (int i = 1; i < argc; i++)
    {
        if (i < argc - 1 && -1 == pipe(pipe_fileno[i - 1]))
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid[i - 1] = fork();
        switch (pid[i - 1])
        {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);

        case 0:
            for (int j = 1; j < i - 1; j++)
            {
                close(pipe_fileno[j - 1][0]);
                close(pipe_fileno[j - 1][1]);
            }

            if (i > 1)
            {
                dup2(pipe_fileno[i - 2][0], STDIN_FILENO);
                close(pipe_fileno[i - 2][1]);
            }

            if (i < argc - 1)
            {
                close(pipe_fileno[i - 1][0]);
                dup2(pipe_fileno[i - 1][1], STDOUT_FILENO);
            }

            if (-1 == execlp(argv[i], argv[i], NULL))
            {
                perror("exec");
                exit(EXIT_FAILURE);
            }
        }
    }

    for (int i = 1; i < argc - 1; i++)
    {
        close(pipe_fileno[i - 1][0]);
        close(pipe_fileno[i - 1][1]);
    }

    for (int i = 1; i < argc - 1; i++)
        waitpid(pid[i - 1], NULL, 0);

    if (argc > 1)
    {
        int status;
        waitpid(pid[argc - 2], &status, 0);
        return WEXITSTATUS(status);
    }
    else
        return EXIT_SUCCESS;
}