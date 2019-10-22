#include <stdlib.h>
#include <stdio.h>

#define REQUIRED_ARG_COUNT 1

int main(int argc, const char *const *argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    FILE *output_file = fopen(argv[1], "w");
    if (NULL == output_file)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char buffer;
    while (!feof(stdin))
    {
        size_t read_count = fread(&buffer, sizeof(char), 1, stdin);
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

        fwrite(&buffer, sizeof(char), read_count, output_file);
        if (ferror(stdout))
        {
            perror("fwrite");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
