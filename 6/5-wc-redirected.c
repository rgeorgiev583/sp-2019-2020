#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define REQUIRED_ARG_COUNT 1

int main(int argc, char *const *argv)
{
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

    if (-1 == execlp("wc", "wc", NULL))
    {
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}