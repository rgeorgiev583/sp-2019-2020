#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define REQUIRED_ARG_COUNT 2

static long from_position_in_line, to_position_in_line;

static void cut(int input_fileno)
{
    char buffer[BUFSIZ];
    ssize_t read_count;
    long current_position_in_line = 0;
    while ((read_count = read(input_fileno, buffer, BUFSIZ)) != 0)
    {
        if (-1 == read_count)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < read_count; i++)
        {
            if ('\n' == buffer[i])
            {
                current_position_in_line = 0;

                if (-1 == write(STDOUT_FILENO, buffer + i, 1))
                {
                    perror("write");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                current_position_in_line++;

                if (current_position_in_line >= from_position_in_line && current_position_in_line <= to_position_in_line)
                {
                    if (-1 == write(STDOUT_FILENO, buffer + i, 1))
                    {
                        perror("write");
                        exit(EXIT_FAILURE);
                    }
                }
            }
        }
    }
}

int main(int argc, const char *const *argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    from_position_in_line = atol(argv[1]);
    if (from_position_in_line <= 0)
        exit(EXIT_FAILURE);

    to_position_in_line = atol(argv[2]);
    if (to_position_in_line <= 0)
        exit(EXIT_FAILURE);

    if (argc > REQUIRED_ARG_COUNT + 1)
    {
        for (int i = REQUIRED_ARG_COUNT + 1; i < argc; i++)
        {
            int input_fileno = open(argv[i], O_RDONLY);
            if (-1 == input_fileno)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }

            cut(input_fileno);

            if (-1 == close(input_fileno))
            {
                perror("close");
                exit(EXIT_FAILURE);
            }
        }
    }
    else
        cut(STDIN_FILENO);

    return EXIT_SUCCESS;
}
