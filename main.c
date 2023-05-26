#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

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
    int input_fd = STDIN_FILENO;
    ssize_t i;
    size_t j;
    char buffer[MAX_COMMAND_LENGTH];
    ssize_t bytes_read;
    ssize_t total_bytes_read = 0;
    size_t command_start = 0;
    size_t remaining_bytes;

    if (argc > 1)
    {
        input_fd = open(argv[1], O_RDONLY);
        if (input_fd == -1)
        {
            perror("Error opening input file");
            return 1;
        }
        
    }

   /* char buffer[MAX_COMMAND_LENGTH];
    ssize_t bytes_read;
    size_t total_bytes_read = 0;*/

    while (1)
    {
        if (isatty (STDIN_FILENO))
	{
            print_string("$ ");
	    fflush(stdout);
	}
        bytes_read = read(input_fd, buffer + total_bytes_read, MAX_COMMAND_LENGTH - total_bytes_read - 1);
        if (bytes_read == -1)
        {
            perror("Error reading input");
            break;
        }
        if (bytes_read == 0)
        {
            
            if (total_bytes_read == 0)
                break;
        }

        total_bytes_read += bytes_read;
        buffer[total_bytes_read] = '\0';

       /* size_t command_start = 0;*/
        for (i = 0; i < total_bytes_read; i++)
        {
            if (buffer[i] == '\n')
            {
                
                size_t command_length = i - command_start;
                _strncpy(command, buffer + command_start, command_length);
                command[command_length] = '\0'; 

               
                remaining_bytes = total_bytes_read - i - 1;
                for (j = 0; j < remaining_bytes; j++)
                    buffer[j] = buffer[i + j + 1];
                total_bytes_read = remaining_bytes;

             
                parse_arguments(command, args, &num_args);
                if (num_args == 0)
                    continue;

                if (is_exit_command(args[0]))
                    return 0; 

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

                command_start = 0; 
            }
        }
    }

    if (input_fd != STDIN_FILENO)
        close(input_fd);

    return 0;
}

