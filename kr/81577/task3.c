#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

// int main()
// {
//     char c = 'c';
//     if(c>' ' && c<'~'){
//         printf("The char is %c", c);
//     }
//     else{
//         printf("no");
//     }
//     return 0;
// }

// int main(int argc, char* const* argv){
//     if(argc>1){
//         for(int i= 1; i<argc; i++){
//             switch(fork()){
//                 case -1:
//                     perror("fork");
//                     exit(EXIT_FAILURE);
                
//                 case 0:
//                 {
//                     int input_fileno = open(argv[i],O_RDONLY);

//                     if(-1 == input_fileno){
//                         perror("open");
//                         exit(EXIT_FAILURE);
//                     }

//                     if(-1 == dup2(input_fileno, STDIN_FILENO)){
//                         perror("dup2");
//                         exit(EXIT_FAILURE);
//                     }

//                     if(-1 == execlp("strings", "strings", NULL)){
//                         perror("execlp");
//                         exit(EXIT_FAILURE);
//                     }
//                 }
//             }

//             if(-1 == wait(NULL)){
//                 perror("wait");
//                 exit(EXIT_FAILURE);
//             }
//         }
//     }
//     else{
//         if(-1 == execlp("strings", "strings", NULL)){
//             perror("execlp");
//             exit(EXIT_FAILURE);
//         }
//     }
//     return EXIT_SUCCESS;
// }


static void strings(int input_fileno){
    char buffer[BUFSIZ];
    ssize_t read_count;
    while((read_count == read(input_fileno, &buffer, BUFSIZ)) !=0){
        if(-1 == read_count){
            perror("read");
            exit(EXIT_FAILURE);
        }
        
        for(int i=0; i<read_count; i++){
            
            if(buffer[i]>=' ' && buffer[i]<= '~'){
                if(-1 == write(STDOUT_FILENO,&buffer[i],1)){
                    perror("write");
                    exit(EXIT_FAILURE);
                }
            }

             else{
                if(-1 == write(STDOUT_FILENO, &buffer, 1)){
                perror("write");
                exit(EXIT_FAILURE);
            }
            }
        }
        
        
    }
}


int main(int argc, char* const* argv){
     if(argc>1){
        for(int i=1; i<argc; i++){
            int input_fileno = open(argv[i], O_RDONLY);
            if(-1 == input_fileno){
                perror("open");
                exit(EXIT_FAILURE);
            }

            strings(input_fileno);
        }
    }
    else{
        strings(STDIN_FILENO);
    }

    return EXIT_SUCCESS;
}