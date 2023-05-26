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

extern char **environ;
/**
 * print_string -a function that prints the symbol
 * @str: the string to print
 * Return; (void)
 */
void print_string(const char *str)
{
	ssize_t len = _strlen(str);
	ssize_t bytes_written = 0;

	while (bytes_written < len)
	{
		ssize_t result = write(STDOUT_FILENO, str + bytes_written, len - bytes_written);
		if (result == -1)
		{
			if (errno == EINTR)
			{
				continue;
			}
			exit(EXIT_FAILURE);
		}
		bytes_written += result;
	}
}

/**
 * read_input -a function that reads the command from the input stream
 * @buffer: the space where the input is store
 * @size: the size of the input
 * Return: (void)
 */
void read_input(char *buffer, size_t size)
{
	ssize_t bytes_read = read(STDIN_FILENO, buffer, size - 1);
	if (bytes_read == -1)
	{
		exit(EXIT_FAILURE);
	}
	buffer[bytes_read] = '\0';
}
/**
 * parse_argument -a function to handle command line with arguments
 * @command: the command passed
 * @args: argument
 * @num_args: number of argument
 * Return: (void)
 */
void parse_arguments(const char *command, char **args, int *num_args)
{
	char *token = strtok((char *)command, " \t\n");
	*num_args = 0;
	
	while (token != NULL && *num_args < MAX_ARGUMENTS)
	{
		args[(*num_args)++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[*num_args] = NULL;
}
/**
 * is_exit_command -a function check if the command is exit
 * to handle exit(0)
 * @command: input command
 * Return: (int)
 */
int is_exit_command(const char *command)
{
	return (_strcmp(command, "exit") == 0);
}
/**
 * is_env_command -a function that checks if the input 
 * command is env to handle env
 * @command: input command
 * Return: an integer
 */
int is_env_command(const char *command)
{
	return (_strcmp(command, "env") == 0);
}
/**
 * is_cd_command -a function to handle the change of 
 * directory
 * @command: the input command
 * Return: an int
 */
int is_cd_command(const char *command)
{
	return (_strcmp(command, "cd") == 0);
}
/**
 * execute_command -a function that execute the 
 * command the user types in
 * @args: arguments
 * Return: (int)
 */
int execute_command(char **args)
{
	char exit_status_str[4];
	pid_t pid = fork();
	if (pid < 0)
	{
		return (-1);
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
        
	int status;
	if (waitpid(pid, &status, 0) == -1)
	{
		return (-1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		print_string("Command '");
		print_string(args[0]);
		print_string("' exited with status ");
		intToStr(WEXITSTATUS(status), exit_status_str, my_sizeof_var(exit_status_str));
		print_string(exit_status_str);
		print_string("\n");
	}
	}
	return (0);
}
/**
 * print_enviroment -a function to print thge env
 * Return: (void)
 */
void print_environment()
{
	char **env = environ;
	
	while (*env != NULL)
	{
		print_string(*env);
		print_string("\n");
		env++;
	}
}
/**
 * change_directory - a function to handle the change of directory
 * @dir: destination directory
 * Return: ( int)
 */
/*int change_directory(char *dir)
{
	if (dir == NULL)
	{
		print_string("Error: No directory specified for 'cd'\n");
		return (-1);
	}
	if (chdir(dir) != 0)
	{
		print_string("Error: Failed to change directory\n");
		return (-1);
	}
	return (0);
}*/
