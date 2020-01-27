#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define REQUIRED_ARG_COUNT 3

int main(int argc, const char* const* argv) {
        if(argc < REQUIRED_ARG_COUNT + 1) {
                exit(EXIT_FAILURE);
        }

        long N = atol(argv[1]);
        long hole_size = N + (81613 % 31) + 31;

        int input_file = open(argv[2],O_RDONLY);
        if(input_file == -1) {
                perror("open");
                exit(EXIT_FAILURE);
        }

        int output_file = open(argv[3],O_WRONLY);
        if(output_file == -1) {
                perror("open");
                exit(EXIT_FAILURE);
        }

        if(-1 == lseek(output_file,hole_size,SEEK_END)) {
                perror("lseek");
                exit(EXIT_FAILURE);
        }

        char buffer;
        int counter;
        while((counter = read(input_file,&buffer,1)) != 0) {
                if(counter  == -1) {
                        perror("read");
                        exit(EXIT_FAILURE);
                }

                if(-1 == write(output_file,&buffer,1)) {
                        perror("write");
                        exit(EXIT_FAILURE);
                }
        }

        return 0;
}

