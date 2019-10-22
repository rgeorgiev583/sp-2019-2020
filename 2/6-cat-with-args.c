#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

static void cat(int input_fileno)
{
    char buffer[BUFSIZ];
    ssize_t read_count;
    while ((read_count = read(input_fileno, buffer, BUFSIZ)) != 0)
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
}

int main(int argc, char const *const *argv)
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            int input_fileno = open(argv[i], O_RDONLY);
            if (-1 == input_fileno)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }

            cat(input_fileno);

            if (-1 == close(input_fileno))
            {
                perror("close");
                exit(EXIT_FAILURE);
            }
        }
    }
    else
        cat(STDIN_FILENO);

    return 0;
}
