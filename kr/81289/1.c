#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define REQUIRED_ARGS_COUNT 3
#define FN 81289

int main(int argc, const char *const *argv)
{
    if (argc < REQUIRED_ARGS_COUNT + 1)
    {
        exit(EXIT_FAILURE);
    }

    long N = atol(argv[1]);
    long append_after = N +(FN % 31) + 5;

    int input_file_d = open(argv[2], O_RDONLY);
    if (input_file_d == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int output_file_d = open(argv[3], O_WRONLY);
    if (output_file_d == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (lseek(output_file_d, append_after, SEEK_END) == -1)
    {
        perror("lseek");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFSIZ];
    ssize_t read_count;
    while ((read_count = read(input_file_d, &buffer, BUFSIZ)) != 0)
    {
        if (input_file_d == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (write(output_file_d, buffer, read_count) == -1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
