#include <unistd.h>
#include <string.h>
#include <stdlib.h>

const static char* ERROR_MESSAGE_FEW_ARGUMENTS = "Expected at least one argument.\n";
const static int ERROR_CODE_FEW_ARGUMENTS = -1;
const static char* ERROR_MESSAGE_READ = "No such process.";
const static int BUFFER_SIZE =  1024;

int main(int argc, char* argv[])
{
	if(argc <= 1)
	{
		write(STDERR_FILENO, ERROR_MESSAGE_FEW_ARGUMENTS, strlen(ERROR_MESSAGE_FEW_ARGUMENTS));
		exit(ERROR_CODE_FEW_ARGUMENTS);
	}
	int i;
	for(i = 1; i < argc; ++i)
	{
		char file[BUFFER_SIZE];
		strcpy(file, "/proc/");
		strcat(file, argv[i]);
		strcat(file, "/cwd");
		write(STDOUT_FILENO, argv[i], strlen(argv[i]));
		write(STDOUT_FILENO, ": ", 2);
		ssize_t readBytes;
		char buffer[BUFFER_SIZE];
		if((readBytes = readlink(file, buffer, BUFFER_SIZE - 1)) < 0)
		{
			write(STDERR_FILENO, ERROR_MESSAGE_READ, strlen(ERROR_MESSAGE_READ));
		}
		write(STDOUT_FILENO, buffer, readBytes);
		write(STDOUT_FILENO, "\n", 1);
	}
}
