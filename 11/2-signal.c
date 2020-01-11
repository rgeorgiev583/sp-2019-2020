#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void)
{
    signal(SIGINT, SIG_IGN);

    while (true)
        ;

    return EXIT_SUCCESS;
}