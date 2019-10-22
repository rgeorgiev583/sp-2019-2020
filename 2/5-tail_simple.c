// XXX: просто, но неефикасно решение

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define REQUIRED_ARG_COUNT 2

int main(int argc, const char *const *argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    long target_count = atol(argv[1]);
    if (target_count < 0)
        exit(EXIT_FAILURE);

    int input_fileno = open(argv[2], O_RDONLY);
    if (-1 == input_fileno)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buffer;
    long total_count = 0;
    ssize_t read_count;
    while (total_count < target_count && (read_count = read(input_fileno, &buffer, 1)) != 0)
    {
        if (-1 == read_count)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        total_count += read_count;
    }

    char wide_buffer[BUFSIZ];
    while ((read_count = read(input_fileno, wide_buffer, BUFSIZ)) != 0)
    {
        if (-1 == read_count)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (-1 == write(STDOUT_FILENO, wide_buffer, read_count))
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
