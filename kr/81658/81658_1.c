/*
Напишете програма, която приема като командни аргументи-  число N и пътищата към два файла и добавя съдържанието на първия
файл към втория файл N + FN % 37 + 6 символа след края му, където FN е факултетният ви номер, а % е операцията остатък при деление.
*/
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc,char* const* argv)
{
    if(argc<4)
    {
        exit(EXIT_FAILURE);
    }
    long hole = atol(argv[1])+81658%37+6;

    int fd1 = open(argv[2], O_RDONLY);
    if (fd1 == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int fd2 = open(argv[3], O_WRONLY);
    if (fd2 == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (lseek(fd2, hole, SEEK_END)==-1)
    {
        perror("lseek");
        exit(EXIT_FAILURE);
    }

    void* buffer;
    ssize_t read_count;
    while ((read_count = read(fd1, buffer, 1)) != 0)
    {
        if (fd1 == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (write(fd2, buffer, read_count)==-1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
