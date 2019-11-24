#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define DEFAULT_FILE_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

#define REQUIRED_ARG_COUNT 2

int main(int argc, const char *const *argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    int base_arg = 1;
    bool do_lseek = false;
    if (0 == strcmp(argv[1], "-l"))
    {
        base_arg = 2;
        do_lseek = true;
    }

    int flags = O_WRONLY | O_CREAT;
    if (do_lseek)
        flags |= O_APPEND;

    int output_fileno = open(argv[base_arg], flags, DEFAULT_FILE_MODE);
    if (-1 == output_fileno)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    long byte_count = atol(argv[base_arg + 1]);
    if (byte_count <= 0)
        exit(EXIT_FAILURE);

    for (long i = 0; i < byte_count; i++)
    {
        if (do_lseek)
        {
            if (-1 == lseek(output_fileno, 0, SEEK_END))
            {
                perror("lseek");
                exit(EXIT_FAILURE);
            }
        }

        if (-1 == write(output_fileno, "x", 1))
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
