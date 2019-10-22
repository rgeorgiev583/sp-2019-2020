#include <stdlib.h>
#include <stdio.h>

#define REQUIRED_ARG_COUNT 2

int main(int argc, const char *const *argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    long target_count = atol(argv[1]);
    if (target_count < 0)
        exit(EXIT_FAILURE);

    FILE *input_file = fopen(argv[2], "r");
    if (NULL == input_file)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char buffer;
    long total_count = 0;
    while (total_count < target_count && !feof(input_file))
    {
        size_t read_count = fread(&buffer, sizeof(char), 1, input_file);
        if (ferror(stdin))
        {
            perror("fread");
            exit(EXIT_FAILURE);
        }

        total_count += read_count;
    }

    while (!feof(input_file))
    {
        size_t read_count = fread(&buffer, sizeof(char), 1, input_file);
        if (ferror(stdin))
        {
            perror("fread");
            exit(EXIT_FAILURE);
        }

        fwrite(&buffer, sizeof(char), read_count, stdout);
        if (ferror(stdout))
        {
            perror("fwrite");
            exit(EXIT_FAILURE);
        }

        total_count += read_count;
    }

    return 0;
}
