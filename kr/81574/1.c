#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

void solve(int n, const char* filename1, const char* filename2) {
    int offset = n + 81574 % 37 + 6;
    int file1 = open(filename1, O_RDONLY);
    int file2 = open(filename2, O_WRONLY);

    if (file1 == -1 || file2 == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    lseek(file2, 0, SEEK_END);
    lseek(file2, offset, SEEK_CUR);

    char buffer[1024] = "";
    int symbols = 0;

    while((symbols = read(file1, buffer, 1024)) > 0) {
        write(file2, buffer, symbols);
    }

    close(file1);
    close(file2);
}

int main(int argc, char** argv) {
    solve(atoi(argv[1]), argv[2], argv[3]);
    exit(EXIT_SUCCESS);
}