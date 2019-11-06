#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_FILE_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

#define REQUIRED_ARG_COUNT 2

int main(int argc, const char *const *argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    int input_fileno = open(argv[1], O_RDONLY);
    if (-1 == input_fileno)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int output_fileno = creat(argv[2], DEFAULT_FILE_MODE);
    if (-1 == output_fileno)
    {
        perror("creat");
        exit(EXIT_FAILURE);
    }

    char buffer;
    ssize_t read_count;
    unsigned long hole_size = 0;
    while ((read_count = read(input_fileno, &buffer, 1)) != 0)
    {
        if (-1 == read_count)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if ('\0' == buffer)
            hole_size++;
        else
        {
            if (hole_size > 0)
            {
                if (-1 == lseek(output_fileno, hole_size, SEEK_CUR))
                {
                    perror("lseek");
                    exit(EXIT_FAILURE);
                }

                hole_size = 0;
            }

            if (-1 == write(output_fileno, &buffer, 1))
            {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}
