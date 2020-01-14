#include <stdlib.h>
#include <stdio.h>

#define REQUIRED_ARG_COUNT 2

int main(int argc, const char *const *argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    FILE *input_file = fopen(argv[1], "r");
    if (NULL == input_file)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    FILE *output_file = fopen(argv[2], "w");
    if (NULL == output_file)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char buffer;
    while (fread(&buffer, sizeof(char), 1, input_file), !feof(input_file))
    {
        if (ferror(input_file))
        {
            perror("fread");
            exit(EXIT_FAILURE);
        }

        fwrite(&buffer, sizeof(char), 1, output_file);
        if (ferror(output_file))
        {
            perror("fwrite");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
