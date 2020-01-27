#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define REQUIRED_ARG_COUNT 1

int main(int argc, const char *const *argv)
{
    if (argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    for(;;)
    {
        printf("%s\n", argv[1]);
    }

    return EXIT_FAILURE;
}
