#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

void solve(int argc, char** argv) {
    int fd[2];
    if (pipe(fd) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // parse params
    strcpy(argv[0], "sort");

    if (pid == 0) {
        // child
        close(1);
        dup(fd[1]);
        close(fd[0]);
        close(fd[1]);
        execvp("sort", argv);

        // should reach this if error only
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // child
        close(0);
        dup(fd[0]);
        close(fd[0]);
        close(fd[1]);
        execlp("uniq", "uniq", NULL);

        // should reach this if error only
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid, NULL, 0);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("not enough params\n");
        exit(EXIT_FAILURE);
    }
    solve(argc, argv);
    exit(EXIT_SUCCESS);
}