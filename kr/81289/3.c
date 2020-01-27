#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    // Hacky solution: but it is as fast as the real strings implementation ;)
    argv[0] = "strings";
    if (-1 == execvp("strings", argv))
    {
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
