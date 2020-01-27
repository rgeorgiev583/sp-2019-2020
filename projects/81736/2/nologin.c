#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(void){

  int fd = open("/etc/nologin.txt", O_RDONLY);

  if(-1 != fd) {
    int count;
    char buffer;
    while((count = read(fd, &buffer, 1)) != 0){
      write(STDOUT_FILENO, &buffer, count);
    }
  }
  else {
   write(STDOUT_FILENO, "The account is currently unavailable.\n", 38);
  }

  exit(1);

}

