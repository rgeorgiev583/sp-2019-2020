#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

/**
 * 1. we do want const char **argv so we cannot change the pointer itself
 * 2. we do not want const char* const* argv as we will modify one of its elements for the sake of easing
 */
int main(int argc, const char **argv) {
    /// first create the pipe descriptors
    int pipe_fd[2];

    /// create pipe from parent
    if (-1 == pipe(pipe_fd)) {
        perror("error piping from parent");
        exit(EXIT_FAILURE);
    }

    /// create the first child for sorting
    int pid_sort = fork();

    if (-1 == pid_sort) {
        perror("error forking sort from parent");
        exit(EXIT_FAILURE);
    }
    /// if we are in sort-child
    else if (0 == pid_sort) {

        /**
         * And now the standard manipulation of descriptors
         * 1. Copy pipe's output to the standard output of the child
         * 2. Close this child's pipe's input and output
         */
        if (-1 == dup2(pipe_fd[1], STDOUT_FILENO)) {
            perror("error dup2 from sort-child");
            exit(EXIT_FAILURE);
        }

        if (-1 == close(pipe_fd[0])) {
            perror("error closing pipe input from sort-child");
            exit(EXIT_FAILURE);
        }

        if (-1 == close(pipe_fd[1])) {
            perror("error closing pipe output from sort-child");
            exit(EXIT_FAILURE);
        }

        /// and finally run the sort command
        argv[1] = "sort";
        if (-1 == execvp("sort", argv + 1)) {
            perror("error execvp from sort-child");
            exit(EXIT_FAILURE);
        }
    }

    /// and now create the second child for uniq
    int pid_uniq = fork();

    if (-1 == pid_uniq) {
        perror("error forking uniq from parent");
        exit(EXIT_FAILURE);
    }
    /// if we are in uniq-child
    else if (0 == pid_sort) {

        /**
         * And now again the standard manipulation of descriptors
         */
        if (-1 == dup2(pipe_fd[0], STDIN_FILENO)) {
            perror("error dup2 from uniq-child");
            exit(EXIT_FAILURE);
        }

        if (-1 == close(pipe_fd[0])) {
            perror("error closing pipe input from sort-child");
            exit(EXIT_FAILURE);
        }

        if (-1 == close(pipe_fd[1])) {
            perror("error closing pipe output from sort-child");
            exit(EXIT_FAILURE);
        }

        /// and finally run the uniq command
        if (-1 == execlp("uniq", "uniq", NULL)) {
            perror("error execlp from uniq-child");
            exit(EXIT_FAILURE);
        }
    }

    /// close pipe's descriptors from the parent as well
    /// only the parents reaches these lines as the children will have their behavior changed by the execlp and execvp
    if (-1 == close(pipe_fd[0])) {
        perror("error closing pipe input from parent");
        exit(EXIT_FAILURE);
    }

    if (-1 == close(pipe_fd[1])) {
        perror("error closing pipe output from parent");
        exit(EXIT_FAILURE);
    }

    /// the parent must wait his children to finish execution
    /// wait for the sort-child to finish
    if (-1 == waitpid(pid_sort, NULL, 0)) {
        perror("error waiting for sort-child from parent");
        exit(EXIT_FAILURE);
    }

    int status;
    if (-1 == waitpid(pid_uniq, &status, 0)) {
        perror("error waiting for uniq-child from parent");
        exit(EXIT_FAILURE);
    }

    /// from the parent say the parent has terminated successfully
    /// but keep the return status of the last terminated child (it might be an error)
    return WEXITSTATUS(status);
}
