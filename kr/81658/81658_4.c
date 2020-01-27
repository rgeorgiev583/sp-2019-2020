/*Да се реализира програмно каналът между две команди sort argv[1..] | uniq.

Забележка: argv[i..] са всички командни аргументи от i-тия натам включително.
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
int main(int argc,char* const* argv)
{
    int fd[2];
    if(pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if(fork()>0)
    {
        if(dup2(fd[1],STDOUT_FILENO)==-1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        if(close(fd[1])==-1)
        {
            perror("close");
            exit(EXIT_FAILURE);
        }
        if(close(fd[0])==-1)
        {
            perror("close");
            exit(EXIT_FAILURE);
        }
        argv[0] = "sort";
        if(execvp("sort",argv+1)==-1)
        {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if(dup2(fd[0],STDIN_FILENO)==-1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);

        }
        if(close(fd[0])==-1)
        {
            perror("close");
            exit(EXIT_FAILURE);
        }
        if(close(fd[1])==-1)
        {
            perror("close");
            exit(EXIT_FAILURE);
        }
        if(execlp("uniq","uniq",0)==-1)
        {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    }
    return EXIT_SUCCESS;
}
