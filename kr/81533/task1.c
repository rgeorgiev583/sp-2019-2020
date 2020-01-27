#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define REQUIRED_ARG_COUNT 3

int main(int argc, const char *const *argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    long N = atol(argv[1]);
    long hole_size = N + 81533%31 + 5;

    int output_fileno = open(argv[3], O_WRONLY);
    if (-1 == output_fileno)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int input_fileno = open(argv[2], O_RDONLY);
    if (-1 == input_fileno)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (-1 == lseek(output_fileno, hole_size, SEEK_END))
    {
        perror("lseek");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFSIZ];
    ssize_t read_count;

    while ((read_count = read(input_fileno, &buffer, BUFSIZ)) != 0)
    {
        if (-1 == input_fileno)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (-1 == write(output_fileno, buffer, read_count))
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
