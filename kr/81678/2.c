#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd1 = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC);
  int fd2 = open(argv[4], O_RDONLY);
  close(0);
  dup(fd2);
  close(1);
  dup(fd1);
  execlp("tr", "tr", argv[1], argv[2], NULL);
}
