#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

static void unexpand(int fd) {
  
  int rCount;
  char buff;
  int blanks = 0;
  char prev;
  read(fd, &prev, 1); // and check it
  if(prev == ' '){
    blanks++;
  }
  else{
    write(STDOUT_FILENO, &prev, 1);
  }
  while(rCount = read(fd, &buff, 1) != 0){
      if(buff == ' '){
        blanks++;
	if(blanks == 8){
	  write(STDOUT_FILENO, "\t", 1);
	  blanks = 0;	  
	}
      }
      else if(buff != ' ' && prev == ' ' && blanks > 0 && blanks < 8){
        int i;
	for(i=0; i < blanks; i++){
	  write(STDOUT_FILENO, " ", 1);
	}
	write(STDOUT_FILENO, &buff, 1);
      }
      else {
        write(STDOUT_FILENO, &buff, 1);
      }
  }
}

int main(int argc, const char* const* argv){
  if (argc < 1){
    unexpand(STDIN_FILENO);
  }
  else{
    int i;
    int fd;    
    for(i = 1; i < argc; i++){
      fd = open(argv[i], O_RDONLY);
      if(-1 == fd){
        perror("open");
        exit(EXIT_FAILURE);
      }
      unexpand(fd);
    }
  }
  exit(EXIT_SUCCESS);
}
