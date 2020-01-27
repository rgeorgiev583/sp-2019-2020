#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define ARG_COUNT 3

int main(int argc, char* argv[]) {
	if(argc != ARG_COUNT + 1) {
		char error[] = "Incorrect number of arguments.\n";
		write(STDOUT_FILENO, error, strlen(error));
		return EXIT_FAILURE;
	}
	
	int fd1 = open(argv[2], O_RDONLY);
	if (fd1 == -1) {
		perror("open fd1");
		return EXIT_FAILURE;
	}
	
	int fd2 = open(argv[3], O_WRONLY);
	if (fd2 == -1) {
		perror("open fd2");
		return EXIT_FAILURE;
	}
	
	const int N = atoi(argv[1]);
	int hole = N + 81646 % 37 + 6;
	lseek(fd2, hole, SEEK_END);

	int bytes;
	char buffer[BUFSIZ];
	while((bytes = read(fd1, buffer, BUFSIZ)) > 0) {
		write(fd2, buffer, bytes);
	}

	return EXIT_SUCCESS;
}
