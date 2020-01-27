#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char buffer[BUFSIZ];
    ssize_t read_count;

    int input_fileno = open('/etc/nologin.txt', O_RDONLY);
    if (-1 == input_fileno)
    {
        printf("The account is currently unavailable.");
    } 
    else
    {
        while ((read_count = read(input_fileno, buffer, BUFSIZ)) != 0)
        {
            if (-1 == read_count)
            {
                perror("read");
                exit(EXIT_FAILURE);
            }

            if (-1 == write(STDOUT_FILENO, buffer, read_count))
            {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }
    }

    return EXIT_FAILURE;
}
