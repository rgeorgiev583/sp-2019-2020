#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define REQUIRED_ARGS 3

int main(int argc, char *argv[]) {
  if (argc < REQUIRED_ARGS + 1) {
    perror("Unexpected number of arguments");
    exit(EXIT_FAILURE);
  }
  int n = atoi(argv[1]);
  int ofset = n + (81678 % 37) + 6;
  int fd1 = open(argv[2], O_RDONLY);
  if (fd1 < 0) {
    perror("File 1 does not exist");
    exit(EXIT_FAILURE);
  }
  int fd2 = open(argv[3], O_WRONLY);
  if (fd2 < 0) {
    perror("File 2 does not exit");
    exit(EXIT_FAILURE);
  }
  lseek(fd2, ofset, SEEK_END);
  char buff[1];
  int size;
  while ((size = read(fd1, buff, 1)) > 0) {
    write(fd2, buff, 1);
  }
}
