#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char buffer[BUFSIZ];
    ssize_t read_count;
    while ((read_count = read(STDIN_FILENO, buffer, BUFSIZ)) != 0)
    {
        if (-1 == read_count)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (-1 == write(STDOUT_FILENO, buffer, read_count))
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
