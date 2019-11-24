#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    argv[0] = "cat";
    if (-1 == execvp("cat", argv))
    {
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}