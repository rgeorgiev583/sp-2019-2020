/*Напишете програма trf, която се извиква по следния начин: trf SET1 SET2 FILE1 FILE2.
Тя трябва да изпълни командата tr SET1 SET2 по такъв начин, че tr да чете от файла FILE2 и да пише във файла FILE1.
Забележка: Ако FILE1 съществува, съдържанието му трябва да се презапише; в противен случай файлът трябва да се създаде.
*/
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* const* argv)
{
    if (argc < 5)
    {
        exit(EXIT_FAILURE);
    }
    const char *set1 = argv[1];

    const char *set2 = argv[2];

    int fd1 = open(argv[3], O_WRONLY);
    if (fd1 == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int fd2 = open(argv[4], O_RDONLY);
    if (fd2==-1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (dup2(fd1, STDIN_FILENO)==-1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    if (dup2(fd2, STDOUT_FILENO)==-1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    if (execlp("tr", "tr", set1, set2, 0)==-1)
    {
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
