#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define REQUIRED_ARG_COUNT 1

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

    if (-1 == dup2(input_fileno, STDIN_FILENO))
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