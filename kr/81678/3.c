#include <fcntl.h>
#include <unistd.h>

static void unexpand(int fd) {
  int tmp = open("tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
  char buff[1];
  int size;
  int intervals = 0;
  while ((size = read(fd, buff, 1)) > 0) {
    if (intervals == 8) {
      write(tmp, "\t", 1);
      intervals = 0;
    }
    if (buff[0] == ' ') {
      ++intervals;
    } else {
      write(tmp, buff, 1);
    }
  }
  while (intervals > 0) {
    write(tmp, " ", 1);
    intervals--;
  }
  ftruncate(fd, 0);
  lseek(tmp,0,SEEK_SET);
  while ((size = read(tmp, buff, 1)) > 0) {
    write(fd, buff, size);
  }
  close(tmp);
}
int main(int argc, char *argv[]) {
  int i;
  for (i = 1; i < argc; ++i) {
    int fd = open(argv[i], O_RDWR);
    close(fd);
  }
}
