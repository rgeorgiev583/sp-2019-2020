#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define REQ_ARGS 3

int main(int argc, const char* const* argv){
    if(argc < REQ_ARGS +1)
    exit(EXIT_FAILURE);

    int space = atol(argv[1]);
    space = space + (81577%31) + 5;

    
    int input_fileno = open(argv[2], O_RDONLY);
    if(-1 == input_fileno){
        perror("open");
        exit(EXIT_FAILURE);
    }

    int output_fileno = open(argv[3], O_WRONLY);
     if(-1 == output_fileno){
        perror("open");
        exit(EXIT_FAILURE);
    }

    if(-1 == lseek(output_fileno,space,SEEK_END)){
        perror("lseek");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFSIZ];
    size_t read_count;
    while((read_count = read(input_fileno,&buffer,BUFSIZ)) != 0){
        if(-1 == read_count){
            perror("read");
            exit(EXIT_FAILURE);
        }

        if(-1 == write(output_fileno,buffer,read_count)){
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;

}