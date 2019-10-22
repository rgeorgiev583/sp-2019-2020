#include <stdlib.h>
#include <stdio.h>

int main(void)
{
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
    }

    return 0;
}
