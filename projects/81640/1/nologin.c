#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

static char* MESSAGE_FILE = "/etc/nologin.txt";
static char* DEFAULT_MESSAGE = "The account is currently unavailable.\n";
static int EXIT_CODE = 1;
static int BUFFER_SIZE = 1024;

int main(int argc, char* argv[])
{
	int fd;
	if((fd = open(MESSAGE_FILE, O_RDONLY)) < 0)
	{
		write(STDOUT_FILENO, DEFAULT_MESSAGE, strlen(DEFAULT_MESSAGE));
		exit(EXIT_CODE);
	}

	ssize_t readBytes;
	char buffer[BUFFER_SIZE];
	while((readBytes = read(fd, buffer, BUFFER_SIZE - 1)) > 0)
	{
		write(STDOUT_FILENO, buffer, readBytes);
	}
	close(fd);
	exit(EXIT_CODE);
}
