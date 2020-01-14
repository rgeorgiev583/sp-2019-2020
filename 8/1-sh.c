#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ARG_COUNT 100
#define PROMPT_STRING "$ "

static char *tokenize_once(char *string, char delimiter)
{
    for (char *i = string; *i != '\0'; i++)
    {
        if (*i == delimiter)
        {
            *i = '\0';
            return i + 1;
        }
    }

    return NULL;
}

int main(int argc, const char *const *argv)
{
    while (true)
    {
        write(STDOUT_FILENO, PROMPT_STRING, sizeof(PROMPT_STRING));

        char command_buffer[BUFSIZ];
        ssize_t command_length = read(STDIN_FILENO, command_buffer, BUFSIZ);
        if (-1 == command_length)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        command_buffer[command_length - 1] = '\0';

        char *command_argv[MAX_ARG_COUNT];
        int command_argc = 0;
        char *current_arg = command_buffer;
        do
        {
            char *next_arg = tokenize_once(current_arg, ' ');
            command_argv[command_argc] = current_arg;
            command_argc++;
            current_arg = next_arg;
        } while (current_arg != NULL);

        if (0 == strcmp(command_argv[0], "exit") || 0 == strcmp(command_argv[0], "quit"))
            exit(EXIT_SUCCESS);

        pid_t pid = fork();
        switch (pid)
        {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);

        case 0:
            if (-1 == execvp(command_argv[0], command_argv))
            {
                fprintf(stderr, "%s: error: command `%s` does not exist\n", argv[0], command_argv[0]);
                exit(EXIT_FAILURE);
            }
        }

        int status;
        wait(&status);
        int exit_status = WEXITSTATUS(status);
        if (exit_status != EXIT_SUCCESS)
            fprintf(stderr, "%s: warning: command `%s` (PID %d) exited with a non-zero status code (%d)\n", argv[0], command_argv[0], pid, exit_status);
    }

    return EXIT_SUCCESS;
}
