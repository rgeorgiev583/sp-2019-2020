#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define REQUIRED_ARG_COUNT 0

void strings(int fd) {
        char buffer;
        int counter;
        char word[1024];
        int j = 0;
        while((counter = read(fd,&buffer,1)) != 0) {
                if(buffer >= ' ' && buffer <= '~') {
                        word[j] = buffer;
                        j++;
                }
                else if(j >= 4) {
                        write(0,&word,j);
                        word[1024];
                        j=0;
                        write(0,"\n",1);
                }
                else {
                        word[1024];
                        j=0;
                }
        }
}
int main(int argc, const char* const* argv) {
        if(argc < REQUIRED_ARG_COUNT + 1) {
                exit(EXIT_FAILURE);
        }

        if(argc > REQUIRED_ARG_COUNT + 1) {
                int i = 1;
                for(i; i<argc; ++i) {
                        int fd =  open(argv[i],O_RDONLY);
                        if(fd == -1) {
                                perror("open");
                                exit(EXIT_FAILURE);
                        }
                        strings(fd);
                }
        }
        else {
                strings(0);
        }

        return 0;
}
