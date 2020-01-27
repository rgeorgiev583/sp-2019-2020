#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_FILE_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

#define REQUIRED_ARG_COUNT 2

int main(int argc, char *const *argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    const char *set2 = argv[1];

    const char *set1 = argv[2];

    if (argc > REQUIRED_ARG_COUNT + 1)
    {
        for (int i = 3; i < argc; i++)
        {
            switch (fork())
            {
            case -1:
                perror("fork");
                exit(EXIT_FAILURE);

            case 0:
            {
                int input_fileno = open(argv[i], O_RDONLY);
                if (-1 == input_fileno)
                {
                    perror("open");
                    exit(EXIT_FAILURE);
                }

                if (-1 == dup2(input_fileno, STDIN_FILENO))
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }

                if (-1 == execlp("tr", "tr", set1, set2, NULL))
                {
                    perror("execlp");
                    exit(EXIT_FAILURE);
                }
            }
            }

            for (int i = 3; i < argc; i++)
            {
                if (-1 == wait(NULL))
                {
                    perror("wait");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    else
    {
        if (-1 == execlp("tr", "tr", set1, set2, NULL))
        {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
