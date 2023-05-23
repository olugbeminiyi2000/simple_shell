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
 * main -program enty point
 * Return: an int (0) is succesful
 */

int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *args[MAX_ARGUMENTS];
	int num_args;

	while (1)
	{
		print_string("$ ");  /*Display prompt*/
		read_input(command, MAX_COMMAND_LENGTH);
		parse_arguments(command, args, &num_args);
		if (num_args == 0)
		{
			continue;
		}
		if (is_exit_command(args[0]))
		{
			break;  /*Exit the shell*/
		}
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
			{
				continue;
			}
			continue;
		}
		execute_command(args);
	}
	return (0);
}
