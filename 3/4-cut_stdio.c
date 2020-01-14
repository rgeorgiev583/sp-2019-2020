#include <stdlib.h>
#include <stdio.h>

#define REQUIRED_ARG_COUNT 2

static long from_position_in_line, to_position_in_line;

static void cut(FILE *input_file)
{
    char buffer;
    long current_position_in_line = 0;
    while (fread(&buffer, sizeof(char), 1, input_file), feof(input_file))
    {
        if (ferror(input_file))
        {
            perror("fread");
            exit(EXIT_FAILURE);
        }

        if ('\n' == buffer)
        {
            current_position_in_line = 0;

            fwrite(&buffer, sizeof(char), 1, stdout);
            if (ferror(stdout))
            {
                perror("fwrite");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            current_position_in_line++;

            if (current_position_in_line >= from_position_in_line && current_position_in_line <= to_position_in_line)
            {
                fwrite(&buffer, sizeof(char), 1, stdout);
                if (ferror(stdout))
                {
                    perror("fwrite");
                    exit(EXIT_FAILURE);
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
            FILE *input_file = fopen(argv[i], "r");
            if (NULL == input_file)
            {
                perror("fopen");
                exit(EXIT_FAILURE);
            }

            cut(input_file);

            if (EOF == fclose(input_file))
            {
                perror("fclose");
                exit(EXIT_FAILURE);
            }
        }
    }
    else
        cut(stdin);

    return EXIT_SUCCESS;
}
