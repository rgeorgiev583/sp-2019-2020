#include <stdbool.h>
#include <stdio.h>
#define REQUIRED_ARGS 1

int main(int argc, const char *const *argv){
  bool infinity = true;
  if(argc < REQUIRED_ARGS + 1){
    while (infinity) {
      puts("y");
    }
  }

  int i = 1;
  while(infinity){
    for(i = 1; i < argc - 1; ++i){
      fputs(argv[i], stdout);
      fputs(" ", stdout);
    }
    puts(argv[i]);
  }
}
