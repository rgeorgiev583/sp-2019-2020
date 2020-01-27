#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void unexpand(int fd)
{
	char buffer[2];
	int count;
	int n;
	while((n = read(fd, buffer, 1)) > 0)
	{
		if(n == -1)
		{
			write(2, "read\n", 5);
			exit(-1);
		}
		if(buffer[0] == ' ')
		{
			if(++count == 8)
			{
				write(1, "\t", 1);
				count = 0;
			}
		}
		else
		{
			if(count > 0)
			{
				write(1, "       ", count);
				count = 0;
			}
			write(1, buffer, 1);
		}
	}
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		unexpand(0);
	}
	else
	{
		int i;
		int fd;
		for(i = 1; i < argc; ++i)
		{
			fd = open(argv[i], O_RDONLY);
			if(fd == -1)
			{
				write(2, "open\n", 5);
			}
			else
			{
				unexpand(fd);
				close(fd);
			}
		}
	}
}
