#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define REQUIRED_ARG_COUNT 1
#define MAX_LINE_LENGTH 80

static const char *pattern;
static long pattern_length;

static void fgrep(FILE *input_file)
{
    do
    {
        char buffer[MAX_LINE_LENGTH];
        long current_line_length = 0;
        while (current_line_length < MAX_LINE_LENGTH && (fread(&buffer[current_line_length], sizeof(char), 1, input_file), (!feof(input_file) && !ferror(input_file))) && buffer[current_line_length] != '\n')
        {
            if (ferror(input_file))
            {
                perror("fread");
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
                fwrite(buffer, sizeof(char), current_line_length, stdout);
                putchar('\n');

                break;
            }
        }
    } while (!feof(input_file));
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
            FILE *input_file = fopen(argv[i], "r");
            if (NULL == input_file)
            {
                perror("fopen");
                exit(EXIT_FAILURE);
            }

            fgrep(input_file);

            if (EOF == fclose(input_file))
            {
                perror("fclose");
                exit(EXIT_FAILURE);
            }
        }
    }
    else
        fgrep(stdin);

    return EXIT_SUCCESS;
}
