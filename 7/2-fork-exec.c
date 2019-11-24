#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#define REQUIRED_ARG_COUNT 1

int main(int argc, char *const *argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    switch (fork())
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);

    case 0:
        if (-1 == execvp(argv[1], argv + 1))
        {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }

    int status;
    if (-1 == wait(&status))
    {
        perror("wait");
        exit(EXIT_FAILURE);
    }

    printf("\n%d\n", WEXITSTATUS(status));

    return EXIT_SUCCESS;
}