#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define REQUIRED_ARGS 1

int main(int argc, const char *const *argv){
  if(argc < REQUIRED_ARGS + 1){
    exit(EXIT_FAILURE);
  }
  int i;
  for(i = 1; i < argc; ++i){
    char path[64] = "/proc/";
    strcat(path, argv[i]);
    strcat(path, "/cwd");
    int size = 1024;
    char buffer[size];
    int read;
    if((read = readlink(path, buffer, size)) < 0){
      exit(1);
    }
    write(0, argv[i], strlen(argv[i]));
    write(0, ": ", 2);
    write(0, buffer, read);
    write(0, "\n", 1);
  }
}
