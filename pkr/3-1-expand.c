#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define TAB_WIDTH 8

static void expand(int input_fileno)
{
    char buffer;
    ssize_t read_result;
    while ((read_result = read(input_fileno, &buffer, 1)) != 0)
    {
        if (-1 == read_result)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if ('\t' == buffer)
        {
            for (int i = 0; i < TAB_WIDTH; i++)
                if (-1 == write(STDOUT_FILENO, " ", 1))
                {
                    perror("write");
                    exit(EXIT_FAILURE);
                }
        }
        else
        {
            if (-1 == write(STDOUT_FILENO, &buffer, 1))
            {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }
    }
}

int main(int argc, const char *const *argv)
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

            expand(input_fileno);
        }
    }
    else
        expand(STDIN_FILENO);

    return EXIT_SUCCESS;
}