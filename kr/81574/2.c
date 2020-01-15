#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

char replaceSymbol(const char* set1, const char* set2, char symbol) {
    char result = symbol;
    int length = strlen(set1); // should be equal to length of set2
    for (int i = 0; i < length; ++i) {
        if (symbol == set1[i]) {
            result = set2[i];
        }
    }
    return result;
}

void solve(const char* set1, const char* set2, const char* filename1, const char* filename2) {
    int file1 = open(filename1, O_CREAT | O_TRUNC | O_WRONLY);
    int file2 = open(filename2, O_RDONLY);

    if (file1 == -1 || file2 == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char symbol;
    char replaced;
    while(read(file2, &symbol, 1) > 0) {
        replaced = replaceSymbol(set1, set2, symbol);
        write(file1, &replaced, 1);
    }

    close(file1);
    close(file2);
}

int main(int argc, char** argv) {
    solve(argv[1], argv[2], argv[3], argv[4]);
    exit(EXIT_SUCCESS);
}