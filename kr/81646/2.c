#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define ARG_COUNT 4

int main(int argc, char* argv[]) {
	if(argc != ARG_COUNT + 1) {
		char error[] = "Incorrect number of arguments.\n";
		write(STDOUT_FILENO, error, strlen(error));
		return EXIT_FAILURE;
	}
	
	int fd2 = open(argv[4], O_RDONLY);
	if (fd2 == -1) {
		perror("open fd2");
		return EXIT_FAILURE;
	}	
	dup2(fd2, STDIN_FILENO);

	int fd1 = open(argv[3], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd1 == -1) {
		perror("open fd1");
		return EXIT_FAILURE;
	}
	dup2(fd1, STDOUT_FILENO);

	if (execlp("tr", "tr", argv[1], argv[2], NULL) == -1) {
		perror("exec");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
