#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

const int BLANK_NUMBER = 8;
const char BLANK = ' ';
const char TAB = '\t';

void unexpand(const char* filename) {
    int input = 0;
    int output = 1;

    if (filename) {
        input = open(filename, O_RDONLY);
        if (input == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
    }

    char symbol;
    int blankCount = 0;
    
    while(read(input, &symbol, 1) > 0) {
        if (symbol == BLANK) {
            ++blankCount;
            if (blankCount == BLANK_NUMBER) {
                // if 8 blanks are found => add \t
                write(output, &TAB, 1);
                blankCount = 0;
            }
        } else {
            if (blankCount < BLANK_NUMBER) {
                // if less than 8 are found => write all of them
                for (int i = 0; i < blankCount; ++i) {
                    write(output, &BLANK, 1);
                }
            }
            write(output, &symbol, 1);
            blankCount = 0;
        }
    }

    if (filename) {
        close(input);
    }
}

void solve(int argc, char** argv) {
    if (argc < 2) {
        // no files args
        unexpand(NULL);
    } else {
        for (int i = 1; i < argc; ++i) {
            unexpand(argv[i]);
            printf("\n");
        }
    }
}

int main(int argc, char** argv) {
    solve(argc, argv);
    exit(EXIT_SUCCESS);
}