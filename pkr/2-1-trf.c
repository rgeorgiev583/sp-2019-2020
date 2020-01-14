#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_FILE_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

#define REQUIRED_ARG_COUNT 4

int main(int argc, char *const *argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    const char *set1 = argv[1];

    const char *set2 = argv[2];

    int output_fileno = creat(argv[3], DEFAULT_FILE_MODE);
    if (-1 == output_fileno)
    {
        perror("creat");
        exit(EXIT_FAILURE);
    }

    int input_fileno = open(argv[4], O_RDONLY);
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

    if (-1 == dup2(output_fileno, STDOUT_FILENO))
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    if (-1 == execlp("tr", "tr", set1, set2, NULL))
    {
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}