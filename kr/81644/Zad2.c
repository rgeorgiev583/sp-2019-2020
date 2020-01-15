#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

/// undefined S_IGRP and S_IROTH ?
///#define DEFAULT_FILE_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
#define DEFAULT_FILE_MODE 644
#define REQUIRED_ARGUMENTS 4

int main(int argc, const char *const *argv) {

    /// check for number of args
    if (argc < REQUIRED_ARGUMENTS + 1) {
		perror("not enough arguments");
		exit(EXIT_FAILURE);
	}

	/// get sets
    const char *set1 = argv[1];
    const char *set2 = argv[2];

    /// get paths
    const char *input_path = argv[4];
    const char *output_path = argv[3];

    /// open files (create output file / truncate it)
    const int input_fd = open(input_path, O_RDONLY);
    const int output_fd = open(output_path, O_CREAT | O_TRUNC, DEFAULT_FILE_MODE);

    /// handle errors
    if (-1 == input_fd) {
        perror("error opening input file");
        exit(EXIT_FAILURE);
    }

    if (-1 == output_fd) {
        perror("error opening output file");
        exit(EXIT_FAILURE);
    }

    /// change standard input/output
    if (-1 == dup2(input_fd, STDIN_FILENO)) {
        perror("error with dup2 input");
        exit(EXIT_FAILURE);
    }

    if (-1 == dup2(output_fd, STDOUT_FILENO)) {
        perror("error with dup2 output");
        exit(EXIT_FAILURE);
    }

    /// finally execute the command 'tr'
    if (-1 == execlp("tr", "tr", set1, set2, NULL)) {
        perror("error with execlp");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
