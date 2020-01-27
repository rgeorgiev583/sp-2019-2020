#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define REQ_ARGS 2

int main(int argc, char* const* argv){
    if(argc < REQ_ARGS+1)
    exit(EXIT_FAILURE);

    const char* set1 = argv[1];
    const char* set2 = argv[2];

    if(argc > REQ_ARGS +1){
        for(int i = 3; i<argc; i++){
            switch(fork()){
                case -1:
                perror("fork");
                exit(EXIT_FAILURE);

                case 0:
                {
                    int input_fileno = open(argv[i],O_RDONLY);
                    if(-1 == input_fileno){
                        perror("open");
                        exit(EXIT_FAILURE);
                    }

                    if(-1 == dup2(input_fileno, STDIN_FILENO)){
                        perror("dup2");
                        exit(EXIT_FAILURE);
                    }

                    if(-1 == execlp("tr", "tr", set2, set1, NULL)){
                        perror("execlp");
                        exit(EXIT_FAILURE);
                    }
                }
            }

            if(-1 == wait(NULL)){
                perror("wait");
                exit(EXIT_FAILURE);
            }
        }
    }
    else
    {
        if(-1 == execlp("tr", "tr", set2, set1, NULL)){
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    }
    
    return EXIT_FAILURE;
}