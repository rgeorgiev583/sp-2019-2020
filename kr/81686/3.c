#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

static void replacer(int fd){
    char buffer[2];
    int spaces_found = 0;
    while(read(fd,buffer,1)){
                if(strcmp(buffer," ")==0){
                    spaces_found++;
                    continue;
                }

                if (spaces_found/8>0){
                    char tmp_buff[2]={'\t','\0'};
                    for(int i =0;i<(spaces_found/8);++i){
                        write(STDOUT_FILENO,tmp_buff,1);
                    }
                }

                if (spaces_found%8>0){
                        char tmp_buff[2]={' ','\0'};
                    for(int i =0;i<(spaces_found%8);++i){
                        write(STDOUT_FILENO,tmp_buff,1);
                    }
                }
                write(STDOUT_FILENO,buffer,1);
                spaces_found=0;
            }
            // In the original command there is no new line (added just to be more clear where a file ends
            buffer[0]='\n';
            buffer[1]='\0';
            write(STDOUT_FILENO,buffer,1);
}


int main(int argc,char** argv)
{

    if (argc < 2){
    replacer(STDIN_FILENO);
    return 0;
    }


   for (int i = 1;i<argc;++i){
        int fd = open(argv[i],O_RDONLY);
        replacer(fd);
        close(fd);
        }

    return 0;
}
