#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define REQUIRED_ARG_COUNT 1

static long total_line_count;

static void head(FILE *input_file)
{
    char buffer;
    long current_line_count = 0;
    while (current_line_count < total_line_count && (fread(&buffer, sizeof(char), 1, input_file), !feof(input_file)))
    {
        if (ferror(input_file))
        {
            perror("fread");
            exit(EXIT_FAILURE);
        }

        if ('\n' == buffer)
            current_line_count++;

        fwrite(&buffer, sizeof(char), 1, stdout);
        if (ferror(stdout))
        {
            perror("fwrite");
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
            FILE *input_file = fopen(argv[i], "r");
            if (NULL == input_file)
            {
                perror("fopen");
                exit(EXIT_FAILURE);
            }

            head(input_file);

            if (EOF == fclose(input_file))
            {
                perror("fclose");
                exit(EXIT_FAILURE);
            }
        }
    }
    else
        head(stdin);

    return EXIT_SUCCESS;
}
