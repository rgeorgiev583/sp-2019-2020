#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc,char** argv)
{
    char buffer;
    int spaces_found = 0;

   for (int i = 1;i<=argc;++i){
        int fd = open(argv[i],O_RDONLY);
        while(read(fd,buffer,1)){
        if(buffer == " "){
            while(buffer == " "){
                spaces_found++;
                read(fd,buffer,1);
            }
            if (spaces_found/8>0){
                while(spaces_found>0){
                    write(STDOUT_FILENO,'\t',1);
                    spaces_found--;
                }
            }
            else{
                while(spaces_found>0){
                    write(STDOUT_FILENO," ",1);
                    spaces_found--;
            }
        }
    }
    else{
        write(STDOUT_FILENO,buffer,1);
    }
   }
   }
    return 0;
}
