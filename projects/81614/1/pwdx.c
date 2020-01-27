#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define REQUIRED_ARG_COUNT 1

int main(int argc,const char* argv[])
{
	if(argc < REQUIRED_ARG_COUNT +1)
	{
		exit(EXIT_FAILURE);
	}
	int i;
	int fd;
	for(i=1;i<argc;i++)
	{
		char file[30] = "/proc/";
		strcat(file,argv[i]);
		strcat(file,"/cwd");
		fd = open(file,O_RDONLY);
		if(fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		ssize_t count;
		char buffer;
		while((count = read(fd,&buffer,1))!=0)
		{
			if(count == -1)
			{
				perror("read");
				exit(EXIT_FAILURE);
			}
			if(write(STDOUT_FILENO,&buffer,1) == -1 )
			{
				perror("write");
				exit(EXIT_FAILURE);
			}
		}
		write(STDOUT_FILENO,"\n",1);
	}
	return EXIT_SUCCESS;
}
			
