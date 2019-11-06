#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define REQUIRED_ARG_COUNT 2

int main(int argc, const char *const *argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    int output_fileno = open(argv[1], O_WRONLY | O_APPEND);
    if (-1 == output_fileno)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    const char *word = argv[2];

    if (-1 == lseek(output_fileno, 0, SEEK_SET))
    {
        perror("lseek");
        exit(EXIT_FAILURE);
    }

    if (-1 == write(output_fileno, word, strlen(word)))
    {
        perror("write");
        exit(EXIT_FAILURE);
    }

    return 0;
}
