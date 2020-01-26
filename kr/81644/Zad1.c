#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define REQUIRED_ARGUMENTS 3

const int FN = 81644;

int main(int argc, const char* const *argv) {
	if (argc < REQUIRED_ARGUMENTS + 1) {
		perror("not enough arguments");
		exit(EXIT_FAILURE);
	}

	const long int N = atol(argv[1]);

	const char *input_path = argv[2];
	const char *output_path = argv[3];

	const int input_fd = open(input_path, O_RDONLY);
	const int output_fd = open(output_path, O_RDONLY);

	if (-1 == input_fd) {
		perror("error opening input file");
		exit(EXIT_FAILURE);
	}

	if (-1 == output_fd) {
		perror("error opening output file");
		exit(EXIT_FAILURE);
	}

	char buffer;
    int hole_size = N + FN % 37 + 6;

    if (-1 == lseek(output_fd, hole_size, SEEK_END)) {
        perror("error with lseek");
        exit(EXIT_FAILURE);
    }

    int read_count = 0;
    while ((read_count = read(input_fd, &buffer, 1)) != 0) {
        if (-1 == read_count) {
            perror("error with read");
            exit(EXIT_FAILURE);
        }

        if (-1 == write(output_fd, &buffer, 1)) {
            perror("error with write");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}
