#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>

int main(void)
{
    if (SIG_ERR == signal(SIGINT, SIG_IGN))
    {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    while (true)
        ;

    return EXIT_SUCCESS;
}