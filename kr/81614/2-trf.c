#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>

#define REQUIRED_ARG_COUNT 4

int main(int argc,char*argv[])
{
    if(argc < REQUIRED_ARG_COUNT + 1)
        exit(EXIT_FAILURE);

    const char* set1 = argv[1];
    const char* set2 = argv[2];

    int fd1 = open(argv[3], O_WRONLY|O_TRUNC|O_CREAT, 0664);
    if(fd1 == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    int fd2 = open(argv[4],O_RDONLY);
    if(fd2 == -1 )
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if((dup2(fd2,STDIN_FILENO)) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    if((dup2(fd1,STDOUT_FILENO)) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    if(execlp("tr","tr",set1,set2,NULL) == -1)
    {
        perror("execlp");
        exit(EXIT_FAILURE);
    }

   exit(EXIT_SUCCESS);
}
