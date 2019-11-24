#include <stdlib.h>
#include <stdio.h>

static void cat(FILE *input_file)
{
    char buffer;
    while (!feof(input_file))
    {
        size_t read_count = fread(&buffer, sizeof(char), 1, input_file);
        if (ferror(input_file))
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
    }
}

int main(int argc, char const *const *argv)
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            FILE *input_file = fopen(argv[i], "r");
            if (NULL == input_file)
            {
                perror("fopen");
                exit(EXIT_FAILURE);
            }

            cat(input_file);

            if (EOF == fclose(input_file))
            {
                perror("fclose");
                exit(EXIT_FAILURE);
            }
        }
    }
    else
        cat(stdin);

    return EXIT_SUCCESS;
}
