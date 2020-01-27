#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int pd[2];
    if (pipe(pd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if (fork())
    {
        close(1);
        dup(pd[1]);
        close(pd[1]);
        close(pd[0]);
        execvp(argv[1], &argv[1])
    }
    else
    {
        close(0);
        dup(pd[0]);
        close(pd[0]);
        close(pd[1]);
        execvp(argv[2], &argv[2]);
    }
}
