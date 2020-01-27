#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

void unexpand(int fd) {
	char buffer[2];
	int spaces = 0;
	while (read(fd, buffer, 1) > 0) {
		if (buffer[0] == ' ') {
			spaces++;
		}
		else {
			while (spaces >= 8) {
				write(STDOUT_FILENO, "\t", 1);
				spaces -= 8;
			}
			while (spaces > 0) {
				write(STDOUT_FILENO, " ", 1);
				spaces--;
			}
			write(STDOUT_FILENO, buffer, 1); 
		}	
	}
	// If the last symbol is a space
	while (spaces >= 8) {
		write(STDOUT_FILENO, "\t", 1);
		spaces -= 8;
	}
	while (spaces > 0) {
		write(STDOUT_FILENO, " ", 1);
		spaces--;	
	}
}

int main(int argc, char* argv[]) {
	
	if (argc == 1) {
		 unexpand(STDIN_FILENO);
	}
	else {
		int i;
		for (i = 1; i < argc; i++) {
			int fd = open(argv[i], O_RDONLY);
			if (fd == -1) {
				write(STDOUT_FILENO, argv[i], strlen(argv[i])); 
				perror(" failed in open");
				write(STDOUT_FILENO, "\n", 1);
				continue;
			}
			dup2(fd, STDIN_FILENO);
			unexpand(fd);
		}			
	}	

	return EXIT_SUCCESS; 
}
