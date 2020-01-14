#include <stdlib.h>
#include <stdio.h>

#define REQUIRED_ARG_COUNT 2

int main(int argc, const char *const *argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    FILE *file1 = fopen(argv[1], "r");
    if (NULL == file1)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    FILE *file2 = fopen(argv[2], "r");
    if (NULL == file2)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char buffer1, buffer2;
    unsigned long current_byte_position = 0, current_line_position = 1;
    do
    {
        fread(&buffer1, sizeof(char), 1, file1);
        if (ferror(file1))
        {
            perror("fread");
            exit(EXIT_FAILURE);
        }

        fread(&buffer2, sizeof(char), 1, file2);
        if (ferror(file2))
        {
            perror("fread");
            exit(EXIT_FAILURE);
        }

        if (feof(file1) || feof(file2))
            break;

        current_byte_position++;
        if ('\n' == buffer1 && '\n' == buffer2)
            current_line_position++;
    } while (buffer1 == buffer2);

    if (!feof(file1) || !feof(file2))
        printf("%s %s differ: byte %ld, line %ld\n", argv[1], argv[2], current_byte_position, current_line_position);

    return EXIT_SUCCESS;
}
