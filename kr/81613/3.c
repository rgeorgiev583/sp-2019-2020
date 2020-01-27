#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define REQUIRED_ARG_COUNT 2

int main(int argc, const char* const* argv) {
        if(argc < REQUIRED_ARG_COUNT + 1) {
                exit(EXIT_FAILURE);
        }

        const char* set1 = argv[1];
        const char* set2 = argv[2];

        if(argc == REQUIRED_ARG_COUNT + 1) {
                if(-1 == execlp("tr","tr",set2,set1,NULL)) {
                        perror("execlp");
                        exit(EXIT_FAILURE);
                }
        }
        else {
                int i = 3;
                for(i; i<argc; ++i) {
                        int kid = fork();
                        if(kid == 0) {
                                int fd = open(argv[i],O_RDONLY);
                                if(fd == -1) {
                                        perror("open");
                                        exit(EXIT_FAILURE);
                                }

                                dup2(fd,0);

                                if(-1 == execlp("tr","tr",set2,set1,NULL)) {
                                        perror("execlp");
                                        exit(EXIT_FAILURE);
                                }
                        }
                }

                i=3;
                for(i; i<argc; ++i) {
                        wait();
                }

        }

        return 0;
}

