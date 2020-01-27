#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<sys/types.h>

static void unexpand(int fd)
{
    int len_spaces = 0;
    char buffer;
    ssize_t read_count;

    while((read_count = read(fd,&buffer,1))>0)
    {
        if(read_count == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if(buffer == '')
        {
            if(len_spaces == 8)
            {
                write(STDOUT_FILENO,'\t',1);
                len_spaces = 0;
            }
            else
                len_spaces++;
        }
        else
            write(STDOUT_FILENO,&buffer,read_count);
    }
}

int main(int argc,char* argv[])
{
    if(argc>1)
    {
        for(int i=1;i<argc;i++)
        {
            int fd = open(argv[i],O_RDONLY);
            if(fd == -1)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
            unexpand(fd);
        }
    }
    unexpand(STDIN_FILENO);

    exit(EXIT_SUCCESS);
}
