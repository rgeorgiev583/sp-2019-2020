#include <stdio.h>
#include <unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	if(argc > 1)
    {
        return 1;
    }
    int fd=open("/etc/nologin.txt",O_RDONLY);
    if(fd != -1)
    {
        ssize_t count;
        void* buffer;
        while(count=read(fd,buffer,1)!=0)
              {
                  write(1,buffer,1);
              }
    }
    else
        {

	puts("This account is currently unavailable");
        }
	return 1;
}




