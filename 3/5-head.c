#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define REQUIRED_ARG_COUNT 1

static ssize_t total_line_count;

static void head(int input_fileno)
{
    char buffer[BUFSIZ];
    ssize_t read_count;
    long current_line_count = 0;
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
                current_line_count++;

            write(STDOUT_FILENO, &buffer, 1);

            if (current_line_count == total_line_count)
                return;
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

            head(input_fileno);

            if (-1 == close(input_fileno))
            {
                perror("close");
                exit(EXIT_FAILURE);
            }
        }
    }
    else
        head(STDIN_FILENO);

    return 0;
}
