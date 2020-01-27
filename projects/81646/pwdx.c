#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ARG_COUNT 1

int main(int argc, char* argv[]) {
	
	if (argc < ARG_COUNT + 1) {
		char error[] = "Incorrect number of arguments.";
		write(STDOUT_FILENO, error, strlen(error));
		return EXIT_FAILURE;
	}
	
	int i;
	for (i = 1; i < argc; i++) {
		char path[] = "/proc/";
		strcat(path, argv[i]);
		strcat(path, "/cwd");
		
		char buffer[BUFSIZ];
		if (readlink(path, buffer, BUFSIZ) == -1) {
			write(STDOUT_FILENO, "PID=", 4);
			write(STDOUT_FILENO, argv[i], strlen(argv[i])); 
			perror(": readlink");
			continue;
		}
		
		int bufferL = strlen(buffer);	
		buffer[bufferL] = '\0';		
		
		char msg[] = "Current working directory of process with PID=";
		write(STDOUT_FILENO, msg, strlen(msg));	
		write(STDOUT_FILENO, argv[i], strlen(argv[i]));
		write(STDOUT_FILENO, ": ", 2);	
		
		write(STDOUT_FILENO, buffer, bufferL);
		write(STDOUT_FILENO, "\n", 1);
	}

	return EXIT_SUCCESS;
}
