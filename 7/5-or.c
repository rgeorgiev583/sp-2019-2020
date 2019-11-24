#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#define REQUIRED_ARG_COUNT 2

static int fork_exec(const char *command_name)
{
    switch (fork())
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);

    case 0:
        if (-1 == execlp(command_name, command_name, NULL))
        {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    }

    int status;
    if (-1 == wait(&status))
    {
        perror("wait");
        exit(EXIT_FAILURE);
    }

    return WEXITSTATUS(status);
}

int main(int argc, const char *const *argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    int exit_status = fork_exec(argv[1]);
    if (EXIT_SUCCESS == exit_status)
        return exit_status;

    exit_status = fork_exec(argv[2]);
    return exit_status;
}