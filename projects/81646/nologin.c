#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
	int fd = open("/etc/nologin.txt", O_RDONLY);
	if (fd == -1) {
		char error[] = "The account is currently unavailable.";
		write(STDOUT_FILENO, error, strlen(error));
	}
	else {
		char buffer[BUFSIZ];
		ssize_t bytes;
		while ((bytes = read(fd, buffer, BUFSIZ)) > 0) {
			write(STDOUT_FILENO, buffer, bytes);
		}
	}
	return EXIT_FAILURE;
}
