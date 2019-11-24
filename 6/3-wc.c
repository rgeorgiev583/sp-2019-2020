#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define REQUIRED_ARG_COUNT 1

int main(int argc, char **argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    if (0 == strcmp(argv[1], "chars"))
        argv[1] = "-c";
    else if (0 == strcmp(argv[1], "words"))
        argv[1] = "-w";
    else if (0 == strcmp(argv[1], "lines"))
        argv[1] = "-l";

    argv[0] = "wc";
    if (-1 == execvp("wc", argv))
    {
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}