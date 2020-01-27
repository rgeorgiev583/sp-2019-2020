#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	if(argc < 5)
	{
		write(2, "argc < 5\n", 9);
		exit(-1);
	}
	int fd0 = open(argv[4], O_RDONLY);
	int fd1 = open(argv[3], O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if(fd0 == -1 || fd1 == -1)
	{
		write(2, "open\n", 5);
		exit(-1);
	}
	close(0);
	dup(fd0);
	close(1);
	dup(fd1);
	execlp("tr", "tr", argv[1], argv[2], NULL);
	write(2, "exec\n", 5);
	exit(-1);
}
