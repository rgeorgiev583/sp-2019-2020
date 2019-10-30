#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define REQUIRED_ARG_COUNT 2

int main(int argc, const char *const *argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    int fileno1 = open(argv[1], O_RDONLY);
    if (-1 == fileno1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int fileno2 = open(argv[2], O_RDONLY);
    if (-1 == fileno2)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buffer1[BUFSIZ], buffer2[BUFSIZ];
    ssize_t read_count1 = 0, read_count2;
    unsigned current_buffer_position = 0, current_byte_position = 0, current_line_position = 1;
    do
    {
        if (current_buffer_position == read_count1)
        {
            read_count1 = read(fileno1, buffer1, BUFSIZ);
            if (-1 == read_count1)
            {
                perror("read");
                exit(EXIT_FAILURE);
            }

            read_count2 = read(fileno2, buffer2, BUFSIZ);
            if (-1 == read_count2)
            {
                perror("read");
                exit(EXIT_FAILURE);
            }

            current_buffer_position = 0;

            if (read_count1 != read_count2 || 0 == read_count1 || 0 == read_count2)
                break;
        }

        current_buffer_position++;
        current_byte_position++;
        if ('\n' == buffer1[current_buffer_position] && '\n' == buffer2[current_buffer_position])
            current_line_position++;
    } while (buffer1[current_buffer_position] == buffer2[current_buffer_position]);

    if (current_buffer_position != 0 || read_count1 != read_count2)
        printf("%s %s differ: byte %ld, line %ld\n", argv[1], argv[2], current_byte_position, current_line_position);

    return 0;
}
