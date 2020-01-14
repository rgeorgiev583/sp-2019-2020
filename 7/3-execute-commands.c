#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *const *argv)
{
    for (int i = 1; i < argc; i++)
    {
        switch (fork())
        {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);

        case 0:
            if (-1 == execlp(argv[i], argv[i], NULL))
            {
                perror("execlp");
                exit(EXIT_FAILURE);
            }
        }
    }

    for (int i = 1; i < argc; i++)
    {
        if (-1 == wait(NULL))
        {
            perror("wait");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}