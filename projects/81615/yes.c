#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>

#define MIN_ARG_COUNT 1

int main(int argc, char * argv[]) {
  if (argc <= MIN_ARG_COUNT) {
    while(1) {
      write(1, "y\n", 2);
    }
  } else {
    while(1) {
      int i = MIN_ARG_COUNT;
      for (i = MIN_ARG_COUNT; i < argc; ++i) {
        int len = strlen(argv[i]);
        write(1, argv[i], len);
        if (i < argc - 1) {
          write(1, " ", 1);
        }
      }
      write(1, "\n", 1);
    }
  }
  exit(EXIT_SUCCESS);
}
