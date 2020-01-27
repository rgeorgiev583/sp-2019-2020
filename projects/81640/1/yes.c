#include <unistd.h>
#include <string.h>

static const int BUFFER_SIZE = 1024;
static char DEFAULT_STRING[2] = "y\n";

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
		for(i = 1; i < argc; ++i)
		{
			strcat(repeat, argv[i]);
			strcat(repeat, " ");
		}
		strcat(repeat, "\n");
	}

	while(1)
	{
		write(STDOUT_FILENO, repeat, strlen(repeat));
	}
}
