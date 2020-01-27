#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>

#define REQUIRED_ARG_COUNT 0

int main(int argc,const char*argv[])
{
	if(argc > REQUIRED_ARG_COUNT + 1)
	{
		return 2;
	}
	int fd;
	fd = open("/etc/nologin.txt",O_RDONLY);
	if(fd == -1)
	{
		write(STDOUT_FILENO,"The account is currently unavailable\n",39);
	}
	ssize_t count;
	char buffer;
	while((count = read(fd,&buffer,1)) !=0)
	{
		if(count == -1)
		{
			exit(EXIT_FAILURE);
		}
		if(write(STDOUT_FILENO,&buffer,1) == -1)
		{
			exit(EXIT_FAILURE);
		}
	}

	return 1;
}
