#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define REQUIRED_ARG_COUNT 1

static long total_line_count;

static void tail(int input_fileno)
{
    char buffer[BUFSIZ];
    ssize_t read_count;
    long current_line_count = 0;
    unsigned long current_buffer_pos;
    while ((read_count = read(input_fileno, buffer, BUFSIZ)) != 0)
    {
        if (-1 == read_count)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        current_buffer_pos = 0;
        for (int i = 0; i < read_count; i++)
        {
            current_buffer_pos++;
            if ('\n' == buffer[i])
                current_line_count++;

            if (current_line_count == total_line_count - 1)
                goto read_write_section;
        }
    }

read_write_section:
    if (-1 == write(STDOUT_FILENO, buffer + current_buffer_pos, read_count - current_buffer_pos))
    {
        perror("write");
        exit(EXIT_FAILURE);
    }

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

int main(int argc, const char *const *argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    total_line_count = atol(argv[1]);
    if (total_line_count < 0)
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

            tail(input_fileno);

            if (-1 == close(input_fileno))
            {
                perror("close");
                exit(EXIT_FAILURE);
            }
        }
    }
    else
        tail(STDIN_FILENO);

    return EXIT_SUCCESS;
}
