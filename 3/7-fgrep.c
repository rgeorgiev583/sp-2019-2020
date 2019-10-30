#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define REQUIRED_ARG_COUNT 1
#define MAX_LINE_LENGTH 80

static const char *pattern;
static long pattern_length;

static void fgrep(int input_fileno)
{
    ssize_t read_count;
    do
    {
        char buffer[MAX_LINE_LENGTH];
        long current_line_length = 0;
        while (current_line_length < MAX_LINE_LENGTH && (read_count = read(input_fileno, &buffer[current_line_length], 1) != 0) && buffer[current_line_length] != '\n')
        {
            if (-1 == read_count)
            {
                perror("read");
                exit(EXIT_FAILURE);
            }

            current_line_length++;
        }

        for (long i = 0; i < current_line_length - pattern_length + 1; i++)
        {
            long j;
            for (j = 0; j < pattern_length; j++)
                if (buffer[i + j] != pattern[j])
                    break;

            if (pattern_length == j)
            {
                write(STDOUT_FILENO, buffer, current_line_length);
                write(STDOUT_FILENO, "\n", 1);

                break;
            }
        }
    } while (read_count != 0);
}

int main(int argc, const char *const *argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    pattern = argv[1];

    pattern_length = strlen(pattern);
    if (pattern_length < 0)
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

            fgrep(input_fileno);

            if (-1 == close(input_fileno))
            {
                perror("close");
                exit(EXIT_FAILURE);
            }
        }
    }
    else
        fgrep(STDIN_FILENO);

    return 0;
}
