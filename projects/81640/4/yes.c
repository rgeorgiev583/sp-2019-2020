#include <unistd.h>
#include <string.h>

const static int BUFFER_SIZE = 1024;
const static char DEFAULT_STRING[3] = "y\n";

int main(int argc, char* argv[])
{
	char repeat[BUFFER_SIZE];

	if(argc == 1)
	{
		strcpy(repeat, DEFAULT_STRING);
	}
	else
	{
		int i;
		strcat(repeat, argv[1]);
		for(i = 2; i < argc; ++i)
		{
			strcat(repeat, " ");
			strcat(repeat, argv[i]);
		}
		strcat(repeat, "\n");
	}

	while(1)
	{
		write(STDOUT_FILENO, repeat, strlen(repeat));
	}
}
