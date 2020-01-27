#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	int fd[2];
	if(pipe(fd) < 0)
	{
		write(2, "pipe\n", 5);
		exit(-1);
	}
	int pid = fork();
	if(pid == -1)
	{
		write(2, "fork\n", 5);
		exit(-1);
	}
	else if(pid == 0)
	{
		close(1);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		if(argc < 2)
		{
			execlp("sort", "sort", NULL);
		}
		else
		{
			argv[0] = "sort";
			execvp("sort", argv);
		}
	}
	else
	{
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		execlp("uniq", "uniq", NULL);
	}
	write(2, "exec\n", 5);
	exit(-1);
}

