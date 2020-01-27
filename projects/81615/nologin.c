#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include<err.h>

#define BUFF_SIZE 1024
// Поне от man 5 nologin пише, че се взима от /etc/nologin, а не /etc/nologin.txt
char nologin_path[] = "/etc/nologin";
char default_message[] = "The account is currently unavailable.";
const char NEWLINE_CONSTANT = '\n';

int main(void) {
  int fd = open(nologin_path, O_RDONLY);
  if (fd < 0) {
    // sizeof - size of buffer, string is one less (\0)
    int left_to_write = sizeof(default_message) - 1;
    int written_bytes = 0;
    while (left_to_write > 0) {
      int currently_written = write(STDOUT_FILENO, default_message + written_bytes, left_to_write + 1 - written_bytes);
      written_bytes  += currently_written;
      left_to_write -= currently_written;
    }

  } else {
    char buffer[BUFF_SIZE];
    int read_count = 0;
    while((read_count = read(fd, buffer, BUFF_SIZE)) > 0) {
      write(STDOUT_FILENO, buffer, read_count);
    }
  }

  write(STDOUT_FILENO, &NEWLINE_CONSTANT, sizeof(NEWLINE_CONSTANT));

  exit(EXIT_FAILURE);
}
