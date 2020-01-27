#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include <fcntl.h>
#include <err.h>
#include <sys/wait.h>

int main(int argc, char*argv[]) {
  if (argc < 3) {
    errx(1, "Invalid number of arguments supplied %d", argc);
    exit(EXIT_FAILURE);
  }
  char * set1 = argv[1];
  char * set2 = argv[2];
  if (argc == 3) {
    // Use with standart input
    execlp("tr", "tr", set2, set1, NULL); 
  } else {

  int i;
  for(i = 3; i < argc; ++i) {
      pid_t child_pid = fork();
  
      if(child_pid == 0) {
        int fd = open(argv[i], O_RDONLY);
        if (fd == -1) {
          errx(2, "No such file %s", argv[i]);
          exit(EXIT_FAILURE);
        }
      
        dup2(fd, 0);
        close(fd);
        execlp("tr", "tr", set2, set1, NULL);
      } else {
        int status;
        waitpid(child_pid, &status, 1);
      } 
    }
  }

  exit(EXIT_SUCCESS);
}
