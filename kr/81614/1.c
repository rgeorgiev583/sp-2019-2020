#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/types.h>

#define REQUIRED_ARG_COUNT 3
#define FN 81614

int main(int argc, char*argv[])
{
    if(argc< REQUIRED_ARG_COUNT +1)
         exit(EXIT_FAILURE);

    long blank_space = atol(argv[1]);

    int fd1 = open(argv[2],O_RDONLY);
    if(fd1 == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    int fd2 = open(argv[3],O_WRONLY);
    if(fd2 == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);

    }
    if((lseek(fd2,blank_space + FN % 37 + 6, SEEK_END)) == -1)
    {
        perror("lseek");
        exit(EXIT_FAILURE);
    }
    char buffer[BUFSIZ];
    ssize_t read_count;
    while((read_count = read(fd1,buffer,BUFSIZ))>0)
    {
        if(read_count == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        if((write(fd2,buffer,read_count))== -1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}
