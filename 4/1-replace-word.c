#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_FILE_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

#define REQUIRED_ARG_COUNT 3

int main(int argc, const char *const *argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    long position = atol(argv[1]);

    const char *word = argv[2];

    int fileno = open(argv[3], O_WRONLY, DEFAULT_FILE_MODE);
    if (-1 == fileno)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (-1 == lseek(fileno, position, position >= 0 ? SEEK_SET : SEEK_END))
    {
        perror("lseek");
        exit(EXIT_FAILURE);
    }

    if (-1 == write(fileno, word, strlen(word)))
    {
        perror("write");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}