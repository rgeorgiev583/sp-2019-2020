#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ARG_COUNT 100

static const char *argv0;

static int fork_exec(char *const *command_argv)
{
    pid_t pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);

    case 0:
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

static int fork_exec_pipe(char *const *input_command_argv, char *const *output_command_argv)
{
    int pipe_fileno[2];
    if (-1 == pipe(pipe_fileno))
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t input_command_pid = fork();
    switch (input_command_pid)
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);

    case 0:
        close(pipe_fileno[0]);
        dup2(pipe_fileno[1], STDOUT_FILENO);

        if (-1 == execvp(input_command_argv[0], input_command_argv))
        {
            fprintf(stderr, "%s: error: command `%s` does not exist\n", argv0, input_command_argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    pid_t output_command_pid = fork();
    switch (output_command_pid)
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);

    case 0:
        dup2(pipe_fileno[0], STDIN_FILENO);
        close(pipe_fileno[1]);

        if (-1 == execvp(output_command_argv[0], output_command_argv))
        {
            fprintf(stderr, "%s: error: command `%s` does not exist\n", argv0, output_command_argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    close(pipe_fileno[0]);
    close(pipe_fileno[1]);

    waitpid(input_command_pid, NULL, 0);

    int status;
    waitpid(output_command_pid, &status, 0);
    int exit_status = WEXITSTATUS(status);
    if (exit_status != 0)
        fprintf(stderr, "%s: warning: command `%s` (PID %d) exited with a non-zero status code (%d)\n", argv0, output_command_argv[0], output_command_pid, exit_status);

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

        int operator_count = 0, operator_types[MAX_ARG_COUNT], subcommand_argv_positions[MAX_ARG_COUNT][2];
        operator_types[operator_count] = 0;
        subcommand_argv_positions[0][0] = 0;
        subcommand_argv_positions[0][1] = -1;
        for (int i = 0; i < command_argc; i++)
        {
            if (0 == strcmp(command_argv[i], "&&"))
            {
                operator_count++;
                operator_types[operator_count] = 1;
                subcommand_argv_positions[operator_count][0] = i + 1;
                subcommand_argv_positions[operator_count][1] = -1;
                command_argv[i] = NULL;
            }
            else if (0 == strcmp(command_argv[i], "||"))
            {
                operator_count++;
                operator_types[operator_count] = 2;
                subcommand_argv_positions[operator_count][0] = i + 1;
                subcommand_argv_positions[operator_count][1] = -1;
                command_argv[i] = NULL;
            }
            else if (0 == strcmp(command_argv[i], "|"))
            {
                subcommand_argv_positions[operator_count][1] = i + 1;
                command_argv[i] = NULL;
            }
        }
        operator_count++;

        int exit_status = 0;
        for (int i = 0; i < operator_count; i++)
        {
            if ((1 == operator_types[i] && 0 != exit_status) || (2 == operator_types[i] && 0 == exit_status))
                break;

            int input_subcommand_argv_position = subcommand_argv_positions[i][0];
            int output_subcommand_argv_position = subcommand_argv_positions[i][1];
            if (-1 == output_subcommand_argv_position)
                exit_status = fork_exec(command_argv + input_subcommand_argv_position);
            else
                exit_status = fork_exec_pipe(command_argv + input_subcommand_argv_position, command_argv + output_subcommand_argv_position);
        }
    }

    return EXIT_SUCCESS;
}
