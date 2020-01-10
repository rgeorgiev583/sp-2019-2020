#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define DEFAULT_FILE_MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

#define MAX_ARG_COUNT 100

static const char *argv0;

static int fork_exec(char *const *command_argv, const char *output_filename, const char *append_filename, const char *input_filename)
{
    pid_t pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);

    case 0:
        if (NULL != output_filename)
        {
            int output_fileno = creat(output_filename, DEFAULT_FILE_MODE);
            if (-1 == output_fileno)
            {
                perror("creat");
                exit(EXIT_FAILURE);
            }

            dup2(output_fileno, STDOUT_FILENO);
        }

        if (NULL != append_filename)
        {
            int append_fileno = open(output_filename, O_WRONLY | O_CREAT | O_APPEND, DEFAULT_FILE_MODE);
            if (-1 == append_fileno)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }

            dup2(append_fileno, STDOUT_FILENO);
        }

        if (NULL != input_filename)
        {
            int input_fileno = open(input_filename, O_RDONLY);
            if (-1 == input_fileno)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }

            dup2(input_fileno, STDIN_FILENO);
        }

        if (-1 == execvp(command_argv[0], command_argv))
        {
            fprintf(stderr, "%s: error: command `%s` does not exist\n", argv0, command_argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    int status;
    wait(&status);
    int exit_status = WEXITSTATUS(status);
    if (exit_status != 0)
        fprintf(stderr, "%s: warning: command `%s` (PID %d) exited with a non-zero status code (%d)\n", argv0, command_argv[0], pid, exit_status);

    return WEXITSTATUS(status);
}

int main(int argc, const char *const *argv)
{
    argv0 = argv[0];

    while (true)
    {
        write(1, "$ ", 2);

        char command_buffer[BUFSIZ];
        ssize_t command_length = read(0, command_buffer, BUFSIZ);
        if (-1 == command_length)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        command_buffer[command_length - 1] = '\0';

        char *command_argv[MAX_ARG_COUNT];
        command_argv[0] = strtok(command_buffer, " ");
        int command_argc = 0;
        do
        {
            command_argc++;
            command_argv[command_argc] = strtok(NULL, " ");
        } while (command_argv[command_argc] != NULL);

        if (0 == strcmp(command_argv[0], "exit") || 0 == strcmp(command_argv[0], "quit"))
            exit(EXIT_SUCCESS);

        int operator_count = 0, operator_types[MAX_ARG_COUNT], next_subcommand_argv_positions[MAX_ARG_COUNT];
        const char *output_filenames[MAX_ARG_COUNT] = {};
        const char *append_filenames[MAX_ARG_COUNT] = {};
        const char *input_filenames[MAX_ARG_COUNT] = {};
        for (int i = 0; i < command_argc; i++)
        {
            if (0 == strcmp(command_argv[i], "&&"))
            {
                operator_types[operator_count] = 1;
                next_subcommand_argv_positions[operator_count] = i + 1;
                command_argv[i] = NULL;
                operator_count++;
            }
            else if (0 == strcmp(command_argv[i], "||"))
            {
                operator_types[operator_count] = 2;
                next_subcommand_argv_positions[operator_count] = i + 1;
                command_argv[i] = NULL;
                operator_count++;
            }
            else if (0 == strcmp(command_argv[i], ">"))
            {
                output_filenames[operator_count] = command_argv[i + 1];
                command_argv[i] = NULL;
            }
            else if (0 == strcmp(command_argv[i], ">>"))
            {
                append_filenames[operator_count] = command_argv[i + 1];
                command_argv[i] = NULL;
            }
            else if (0 == strcmp(command_argv[i], "<"))
            {
                input_filenames[operator_count] = command_argv[i + 1];
                command_argv[i] = NULL;
            }
        }

        int exit_status = fork_exec(command_argv, output_filenames[0], append_filenames[0], input_filenames[0]);
        for (int i = 0; i < operator_count; i++)
        {
            if ((1 == operator_types[i] && 0 != exit_status) || (2 == operator_types[i] && 0 == exit_status))
                break;

            int subcommand_argv_position = next_subcommand_argv_positions[i];
            exit_status = fork_exec(command_argv + subcommand_argv_position, output_filenames[i + 1], append_filenames[i + 1], input_filenames[i + 1]);
        }
    }

    return EXIT_SUCCESS;
}
