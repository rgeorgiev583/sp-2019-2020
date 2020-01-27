#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include <fcntl.h>
#include <err.h>

#define FN_CONST 5 + 81615 % 31

int main(int argc, char*argv[]) {
  if (argc < 3) {
    errx(1, "Invalid number of arguments supplied %d", argc);
    exit(EXIT_FAILURE);
  }
  char * lines = argv[1];
  int N = atoi(lines);
  char * file1 = argv[2];
  char * file2 = argv[3];
  
  int file1_fd = open(file1, O_RDONLY);
  if (file1_fd == -1) {
      errx(-1, "Error opening file %s", file1);
      exit(EXIT_FAILURE);
  }

  int file2_fd = open(file2, O_WRONLY);
  if (file2_fd == -1) {
      errx(-1, "Error opening file %s", file2);
      exit(EXIT_FAILURE);
  }

  lseek(file2_fd, FN_CONST + N, SEEK_END);

  const int BUFF_SIZE = 10;
  char buffer[BUFF_SIZE];
  int res = 0;
  while((res = read(file1_fd, buffer, BUFF_SIZE)) > 0) {
    write(file2_fd, buffer, res);
  }

  exit(EXIT_SUCCESS);
}
