#include<unistd.h>
#include<errno.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#include<err.h>

#define MIN_ARG_COUNT 1

// PATH_MAX comes from limits.h
// usually the longest possible path length
// It's supposedly a guideline, not an actual upper length
// but I guess it will do for this.
#ifndef PATH_MAX 
#define PATH_MAX 4096 
#endif

char base_path[] = "/proc/";
char file_name[] = "cwd";

bool check_number(char * number) {
 while(*number) {
    if(*number < '0' || *number > '9') {
      return false;
    }
   number++;
 }
 return true;
}

int main(int argc, char * argv[]) {
  if (argc == MIN_ARG_COUNT) {
    errx(1, "Usage: pwdx PID [PID...]");
  } else {
    for (int i = MIN_ARG_COUNT; i < argc; ++i) {
      if(!check_number(argv[i])) {
        errx(2, "Invalid PID %s\n", argv[i]);
        continue;
      }
      char pwd_path[PATH_MAX] = {};
      strcat(pwd_path, base_path);
      strcat(pwd_path, argv[i]);
      strcat(pwd_path, "/");
      strcat(pwd_path, file_name);
      
      char buffer[PATH_MAX];
      int res = readlink(pwd_path, buffer ,PATH_MAX);
      if(res == -1) {
        perror(argv[i]);
      } else {
        // readlink() does not append  a  null byte  to buf.
        // So we do it manually
        // res has the number of written bytes
        // The compiler moves the char buffer[PATH_MAX] outside the for loop
        // so it leaves part of the longest path in the buffer for the next iteraiton.
        // Compiler optimizations sometimes have unexpected side effects :D
        buffer[res] = '\0';
        char output[PATH_MAX] = {};
        strcat(output, argv[i]);
        strcat(output, ": ");
        strcat(output, buffer);
        strcat(output, "\n");
        int length = strlen(output);
        int written_bytes = 0;
        while(written_bytes < length) {
          written_bytes += write(STDOUT_FILENO, output + written_bytes, length - written_bytes);
        }
      }
    }
  }
  exit(EXIT_SUCCESS);
}
