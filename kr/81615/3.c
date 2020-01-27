#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include <fcntl.h>
#include <err.h>
#include <sys/wait.h>

#define MIN_LENGHT 4
#define READABLE_SYMBOLS_START 32
#define READABLE_SYMBOLS_END 126

#define BUFF_SIZE 100

int is_valid_symbol(char c) {
  return c >= READABLE_SYMBOLS_START && c <= READABLE_SYMBOLS_END;
}

void get_strings_from_fd_to_fd(int fd_in, int fd_out) {
  char buffer;
  char readable_word[MIN_LENGHT];
  int read_bytes;
  int buffer_filled = 0;

  int is_printed = 0;

  // Slow but will work, adding a buffer will complicate it 
  while((read_bytes = read(fd_in, &buffer, 1)) > 0) {
    if(is_valid_symbol(buffer)) {
      if(!is_printed) {
        readable_word[buffer_filled] = buffer;
        buffer_filled++;
      } else {
        write(fd_out, &buffer, 1);
      }
    } else {
      if(is_printed) {
        char c = '\n';
        write(fd_out, &c, 1);
      }
      buffer_filled = 0;
      is_printed = 0;
    }

    if (!is_printed && buffer_filled == MIN_LENGHT) {
       is_printed = 1;
       write(fd_out, readable_word ,MIN_LENGHT);
    }
  }
}

void get_strings_from_fd(int fd_in) {
  get_strings_from_fd_to_fd(fd_in, 1);
}


int main(int argc, char*argv[]) {
  if (argc == 1) {
    get_strings_from_fd(0);
  } else {
    int i = 1;
    for(i = 1; i < argc; ++i) {
      int fd = open(argv[i], O_RDONLY);
      if(fd < 0) {
        errx(1, "Error reading file %s", argv[i]);
      } else {
        get_strings_from_fd(fd);
        close(fd);
      }
    }
  }

  exit(EXIT_SUCCESS);
}
