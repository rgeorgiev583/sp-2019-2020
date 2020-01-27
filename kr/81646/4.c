#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define ARG_COUNT 1

int main(int argc, char* argv[]) {
	if(argc < ARG_COUNT + 1) {
		char error[] = "Incorrect number of arguments.\n";
		write(STDOUT_FILENO, error, strlen(error));
		return EXIT_FAILURE;
	}

	int fd[2];
	pipe(fd);
	
	int firstP = fork();
	if (firstP == 0) {
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		argv[0] = "sort";
		if (execvp(argv[0], argv) == -1) {
			perror("exec1");
			return EXIT_FAILURE;
		}
	}
	
	int secondP = fork();
	if (secondP == 0) {
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		if (execlp("uniq", "uniq", NULL) == -1) {
			perror("exec2");
			return EXIT_FAILURE;
		}
	}
	
	close(fd[0]);
	close(fd[1]);
	
	waitpid(firstP, NULL, 0);
	waitpid(secondP, NULL, 0);
	
	return EXIT_SUCCESS;
}
