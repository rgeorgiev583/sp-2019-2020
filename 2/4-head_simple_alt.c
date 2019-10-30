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

    char buffer[BUFSIZ];
    long total_count = 0;
    ssize_t read_count;
    while ((read_count = read(input_fileno, buffer, BUFSIZ)) != 0)
    {
        if (-1 == read_count)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < read_count; i++)
        {
            if (-1 == write(STDOUT_FILENO, buffer + i, 1))
            {
                perror("write");
                exit(EXIT_FAILURE);
            }

            total_count++;
            if (total_count == target_count)
                return 0;
        }
    }

    return 0;
}
