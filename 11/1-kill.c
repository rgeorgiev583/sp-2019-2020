#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, const char *const *argv)
{
    for (int i = 1; i < argc; i++)
    {
        int pid = atoi(argv[i]);
        if (0 == pid)
            exit(EXIT_FAILURE);

        if (-1 == kill(pid, SIGTERM))
        {
            perror("kill");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}