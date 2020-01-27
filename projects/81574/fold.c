#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char NEWLINE = '\n';

int readWhile(int fd, char* buffer, int length) {
  char symbol;
  int symbolsRead = 0;
  int i;
  for (i = 0; i < length; ++i) {
    symbolsRead = read(fd, &symbol, 1);
    // cant read anymore
    if (symbolsRead == 0) {
      return symbolsRead;
    }
    buffer[i] = symbol;
    // newline found
    if (symbol == NEWLINE) {
      break;
    }
    // length reached
    if (i + 1 == length) {
      buffer[i + 1] = '\n';
    }
  }
  return i + 1;
}

void fold(char* filename, int lineSize) {
  int fd = 0;
  if (filename) {
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
      perror("open");
      exit(EXIT_FAILURE);
    }
  }

  int symbols = 0;
  char buffer[1024] = "";

  while((symbols = readWhile(fd, buffer, lineSize)) > 0) {
    write(1, buffer, symbols);
  }

  if (filename) {
    close(fd);
  }
}

int main(int argc, char** argv) {
  int lineSize = 80;
  bool filePassed = false;

  // handle all options first
  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      // if argument is "-w" option
      if (argv[i][1] == 'w') {
        lineSize = atoi(argv[i] + 2);
        if (lineSize == 0) {
          // wrong line size
          printf("Invalid number of columns.");
        }
      } else {
        // unknown param
      }
    }
  }

  // handle file arguments
  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] != '-') {
      filePassed = true;
      fold(argv[i], lineSize);
    }
  }

  if (!filePassed) {
    fold(NULL, lineSize);
  }

  return EXIT_SUCCESS;
}
