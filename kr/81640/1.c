#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	if(argc < 4)
	{
		write(2, "argc < 4\n", 9);
		exit(-1);
	}
	int fd1 = open(argv[2], O_RDONLY);
	int fd2 = open(argv[3], O_WRONLY);
	if(fd1 == -1 || fd2 == -1)
	{
		write(2, "open\n", 5);
		exit(-1);
	}
	int n = atoi(argv[1]);
	int set = n + 81640 % 37 + 6;
	lseek(fd2, set, SEEK_END);
	int bytes;
	char buffer[1024];
	while((bytes = read(fd1, buffer, 1024)) > 0)
	{
		if(bytes == -1)
		{
			write(2, "read\n", 5);
			exit(-1);
		}
		write(fd2, buffer, bytes);
	}
}
