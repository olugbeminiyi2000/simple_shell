#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
/**
 * execute_logical_commands - Execute commands based on logical operators
 * @commands: Array of commands
 * @num_commands: Number of commands
 */
void execute_logical_commands(char **commands, int num_commands)
{
    int i;
    int status;
   char *args[MAX_ARGUMENTS];
   int num_args;
   char exit_status_str[4];
    for (i = 0; i < num_commands; i++)
    {
        

        parse_arguments(commands[i], args, &num_args);

        if (is_exit_command(args[0]))
        {
            exit(0);
        }
        else if (is_env_command(args[0]))
        {
            print_environment();
        }
        else if (is_cd_command(args[0]))
        {
            if (num_args < 2)
            {
                print_string("Error: No directory specified for 'cd'\n");
                continue;
            }
            if (change_directory(args[1]) != 0)
            {
                continue;
            }
        }
        else
        {
            pid_t pid = fork();

            if (pid < 0)
            {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }
            else if (pid == 0)
            {
                
                int result = execvp(args[0], args);
                if (result == -1)
                {
                    print_string("Error: Command '");
                    print_string(args[0]);
                    print_string("' not found\n");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                
                if (waitpid(pid, &status, 0) == -1)
                {
                    perror("waitpid failed");
                    exit(EXIT_FAILURE);
                }
                if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
                {
                    print_string("Command '");
                    print_string(args[0]);
                    print_string("' exited with status ");
                   /* char exit_status_str[4];*/
                    intToStr(WEXITSTATUS(status), exit_status_str, sizeof(exit_status_str));
                    print_string(exit_status_str);
                    print_string("\n");
                }
            }
        }
    }
}

