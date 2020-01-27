#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#define REQUIRED_ARGS_COUNT 2

int main(int argc, char *const *argv)
{
    if (argc < REQUIRED_ARGS_COUNT + 1)
    {
        exit(EXIT_FAILURE);
    }

    const char *set_1 = argv[2];
    const char *set_2 = argv[1];

    if (argc > REQUIRED_ARGS_COUNT + 1)
    {
        for (int i = 3; i < argc; i++)
        {
            switch (fork())
            {
                case -1:
                {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }
                case 0:
                {
                    int input_file_d = open(argv[i], O_RDONLY);
                    if (input_file_d == -1)
                    {
                        perror("open");
                        exit(EXIT_FAILURE);
                    }

                    if (dup2(input_file_d, STDIN_FILENO) == -1)
                    {
                        perror("dup2");
                        exit(EXIT_FAILURE);
                    }

                    if (execlp("tr", "tr", set_1, set_2, NULL) == -1)
                    {
                        perror("execlp");
                        exit(EXIT_FAILURE);
                    }
                }
            }

            for (int i = 3; i < argc; i++)
            {
                if (wait(NULL) == -1)
                {
                    perror("wait");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    else
    {
        if (execlp("tr", "tr", set_1, set_2, NULL) == -1)
        {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
