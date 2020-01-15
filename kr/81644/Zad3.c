#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define SPACES_TOTAL 8

void unexpand(const int fd) {
    char buffer;
    int read_count = 0;
    int spaces_count = 0;

    while ((read_count = read(fd, &buffer, 1)) != 0) {
        if (-1 == read_count) {
            perror("error with reading from input");
            exit(EXIT_FAILURE);
        }

        if (' ' == buffer) {
            ++spaces_count;
        }
        else {
            /// check if we need a tabulation
            if (spaces_count == SPACES_TOTAL) {
                /// make a cast for the tabulation
                if (-1 == write(STDOUT_FILENO, (const void*)'\t', 1)) {
                    perror("error writing a tabulation");
                    exit(EXIT_FAILURE);
                }

                spaces_count = 0;
            }
            else {
                /// print all read spaces so far
                for (int i = 0; i < spaces_count; ++i) {
                    if (-1 == write(STDOUT_FILENO, " ", 1)) {
                        perror("error writing spaces");
                        exit(EXIT_FAILURE);
                    }
                }

                /// then print the current symbol
                if (-1 == write(STDOUT_FILENO, &buffer, 1)) {
                    perror("error writing (printing) content of input");
                    exit(EXIT_FAILURE);
                }

                spaces_count = 0;
            }
        }
    }
}

int main(int argc, const char *const *argv) {

    /// if we have a file
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            const int input_fd = open(argv[i], O_RDONLY);
            if (-1 == input_fd) {
                perror("error with opening file");
                exit(EXIT_FAILURE);
            }

            unexpand(input_fd);
        }
    }
    /// else read from standard input
    else {
        unexpand(STDIN_FILENO);
    }

    return EXIT_SUCCESS;
}
