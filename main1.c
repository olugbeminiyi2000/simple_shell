#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

/**
 * main - program entry point
 * @argc: number of command-line arguments
 * @argv: array of command-line arguments
 * Return: an int (0) if successful
 */

int main(int argc, char *argv[])
{
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGUMENTS];
    int num_args;
    FILE *input_stream;

    if (argc > 1) {
        input_stream = fopen(argv[1], "r");
        if (!input_stream) {
            perror("Error opening input file");
            return 1;
        }
    } else {
        input_stream = stdin; // Read from standard input
    }

    while (1)
    {
        if (input_stream == stdin)
            print_string("$ "); /* Display prompt */

        if (fgets(command, sizeof(command), input_stream) == NULL)
            break; /* End of input */

        command[strcspn(command, "\n")] = '\0'; // Remove trailing newline

        parse_arguments(command, args, &num_args);
        if (num_args == 0)
            continue;

        if (is_exit_command(args[0]))
            break; /* Exit the shell */

        if (is_env_command(args[0]))
        {
            print_environment();
            continue;
        }

        if (is_cd_command(args[0]))
        {
            if (num_args < 2)
            {
                print_string("Error: No directory specified for 'cd'\n");
                continue;
            }
            if (change_directory(args[1]) != 0)
                continue;
            continue;
        }

        execute_command(args);
    }

    if (input_stream != stdin)
        fclose(input_stream);

    return 0;
}

