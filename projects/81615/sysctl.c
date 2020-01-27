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

#ifndef PATH_MAX 
#define PATH_MAX 4096 
#endif

#define BUF_SIZE 1024

const char base_path[] = "/proc/sys/";
const char EQUALS_CONSTANT = '=';
const char SPACE_CONSTANT = ' ';
const char NEWLINE_CONSTANT = '\n';

int contains_char(char c, char * str) {
  int i = 0;
  while(*str) {
    if(c == *str) {
      return i;
    }
    i++;
    str++;
  }

  return -1;
}

int main(int argc, char * argv[]) {
  if (argc == MIN_ARG_COUNT) {
    errx(1, "Usage: sysctl [NAME|NAME=VALUE...]");
  } else {
    for (int i = MIN_ARG_COUNT; i < argc; ++i) {
     char path[PATH_MAX] = {};
     strcat(path, base_path);
     int pos = contains_char(EQUALS_CONSTANT, argv[i]);

     // By doing this we effectively split argv[i] into setting and value
     char * setting = argv[i];
     if (pos != -1) {
        argv[i][pos] = '\0';
     }
     char sub_path[PATH_MAX];
     strcpy(sub_path, setting);
     for(int k = 0; sub_path[k]; ++k) {
        if (sub_path[k] == '.') {
          sub_path[k] = '/';
        }
     }
     strcat(path, sub_path);

     // This means we don't have an equals, thus it's just fetching a property.
     if(pos == -1) {
        int fd = open(path, O_RDONLY);
        if (fd == -1) {
          perror(path);
          continue;
        }
        int written_bytes = 0;
        int current_written_bytes = 0;
        int length = strlen(argv[i]);
        while((current_written_bytes = write(STDOUT_FILENO, argv[i] + written_bytes, length - written_bytes)) > 0) { 
          written_bytes += current_written_bytes;
        }
        // This is just how the normal sysctl looks (with spaces)
        write(STDOUT_FILENO, &SPACE_CONSTANT, sizeof(SPACE_CONSTANT)); 
        write(STDOUT_FILENO, &EQUALS_CONSTANT, sizeof(EQUALS_CONSTANT)); 
        write(STDOUT_FILENO, &SPACE_CONSTANT, sizeof(SPACE_CONSTANT)); 
        char buffer[BUF_SIZE];
        int read_bytes = 0;
        while((read_bytes = read(fd, buffer, BUF_SIZE)) > 0) {
          write(STDOUT_FILENO, buffer, read_bytes);
        }
     } else {
        // This means we have an equals, so we have to SET a property.  
        // Judging by sysctl, if a file does not exist, it isn't created.  
        char * value = argv[i] + pos + 1;
        int fd = open(path, O_WRONLY | O_TRUNC); 
        if (fd == -1) {
          perror(path);
          continue;
        }

        int written_bytes = 0;
        int current_written_bytes = 0;
        int length = strlen(value);
        while((current_written_bytes = write(fd, value + written_bytes, length - written_bytes)) > 0) { 
          written_bytes += current_written_bytes;
        }
        written_bytes = 0;
        current_written_bytes = 0;
        length = strlen(argv[i]);
        while((current_written_bytes = write(STDOUT_FILENO, argv[i] + written_bytes, length - written_bytes)) > 0) { 
          written_bytes += current_written_bytes;
        }
        
        write(STDOUT_FILENO, &SPACE_CONSTANT, sizeof(SPACE_CONSTANT)); 
        write(STDOUT_FILENO, &EQUALS_CONSTANT, sizeof(EQUALS_CONSTANT)); 
        write(STDOUT_FILENO, &SPACE_CONSTANT, sizeof(SPACE_CONSTANT)); 

        written_bytes = 0;
        current_written_bytes = 0;
        length = strlen(value);
        while((current_written_bytes = write(STDOUT_FILENO, value + written_bytes, length - written_bytes)) > 0) { 
          written_bytes += current_written_bytes;
        }

        write(STDOUT_FILENO, &NEWLINE_CONSTANT, sizeof(NEWLINE_CONSTANT)); 
     }
    }
  }
  exit(EXIT_SUCCESS);
}
