#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, const char *const *argv)
{
    int sig_number = SIGTERM;
    int pid_start = 1;

    if (strcmp(argv[1], "-s"))
    {
        sig_number = atoi(argv[2]);
        if (0 == sig_number)
            exit(EXIT_FAILURE);
        pid_start = 3;
    }
    else if (argv[1][0] == '-') 
    {
        sig_number = atoi(argv[1][1]);
        if (0 == sig_number)
            exit(EXIT_FAILURE);
        pid_start = 2;
    } 

    for (int i = pid_start; i < argc; i++)
    {
        int pid = atoi(argv[i]);
        if (0 == pid)
            exit(EXIT_FAILURE);

        if (-1 == kill(pid, sig_number))
        {
            perror("kill");
            exit(EXIT_FAILURE);
        }
    }
    
    return EXIT_SUCCESS;
}