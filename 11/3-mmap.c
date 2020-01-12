#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MESSAGE "Hello world"
#define MESSAGE_LENGTH sizeof(MESSAGE)

int main(void)
{
    char *message = mmap(NULL, MESSAGE_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    switch (fork())
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);

    case 0:
        strcpy(message, MESSAGE);
        exit(EXIT_SUCCESS);

    default:
        wait(NULL);
        write(STDOUT_FILENO, message, MESSAGE_LENGTH);
    }

    return EXIT_SUCCESS;
}