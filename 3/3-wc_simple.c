#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

static unsigned long total_byte_count = 0, total_line_count = 0;

static void wc(int input_fileno, const char *filename)
{
    char buffer;
    ssize_t read_count;
    unsigned long byte_count = 0, line_count = 0;
    while ((read_count = read(input_fileno, &buffer, 1)) != 0)
    {
        if (-1 == read_count)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        byte_count++;
        if ('\n' == buffer)
            line_count++;
    }

    if (NULL == filename)
        printf(" %ld %ld\n", line_count, byte_count);
    else
        printf(" %ld %ld %s\n", line_count, byte_count, filename);

    total_byte_count += byte_count;
    total_line_count += line_count;
}

int main(int argc, const char *const *argv)
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            int input_fileno = open(argv[i], O_RDONLY);
            if (-1 == input_fileno)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }

            wc(input_fileno, argv[i]);

            if (-1 == close(input_fileno))
            {
                perror("close");
                exit(EXIT_FAILURE);
            }
        }
    }
    else
        wc(STDIN_FILENO, NULL);

    printf(" %ld %ld total\n", total_line_count, total_byte_count);

    return EXIT_SUCCESS;
}
