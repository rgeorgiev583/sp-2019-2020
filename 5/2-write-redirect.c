#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_FILE_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

#define REQUIRED_ARG_COUNT 1

int main(int argc, const char *const *argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    int output_fileno = creat(argv[1], DEFAULT_FILE_MODE);
    if (-1 == output_fileno)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (-1 == dup2(output_fileno, STDOUT_FILENO))
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFSIZ];
    ssize_t read_count;
    while ((read_count = read(STDIN_FILENO, buffer, BUFSIZ)) != 0)
    {
        if (-1 == read_count)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (-1 == write(STDOUT_FILENO, &buffer, read_count))
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}