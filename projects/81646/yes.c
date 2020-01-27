#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	if (argc == 1) {
		while(1) {
			write(STDOUT_FILENO, "y\n", 2);
		}
	}
	else {
		while(1) {
			int i;
			for(i = 1; i < argc; i++) {
				ssize_t stat = write(STDOUT_FILENO, argv[i], strlen(argv[i]));
				if (stat < 0) {
					perror("write: ");
					return EXIT_FAILURE;
				}
				if (i != argc - 1) {
					write(STDOUT_FILENO, " ", 1);
				}
			}
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	return EXIT_SUCCESS;
}
