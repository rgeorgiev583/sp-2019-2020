#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define TABS 8

static void unexpand(int input_fileno)
{
    char buffer;
    ssize_t read_result;
    int cnt = 0;
    char t = '\t'
    while ((read_result = read(input_fileno, &buffer, 1)) != 0)
    {
        if (-1 == read_result)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (' ' == buffer)
        {
          do
          { 
             (read_result = read(input_fileno, &buffer, 1);
             if (-1 == read_result)
                {
                   perror("read");
                   exit(EXIT_FAILURE);
                }
             cnt++;
          }while(' ' == buffer)
        if(TABS == cnt)
        {
          if(-1 == write(STDOUT_FILENO, t, 1))
          {
                perror("write");
                exit(EXIT_FAILURE);
          }
        }
        else
        {
            if (-1 == write(STDOUT_FILENO, &buffer, 1))
            {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }
    }
}

int main(int argc, const char *const *argv)
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            int input_fileno = open(argv[i], O_RDONLY);
            if (-1 == input_fileno)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }

            unxpand(input_fileno);
        }
    }
    else
        unexpand(STDIN_FILENO);

    return EXIT_SUCCESS;
}
        
             