#include "main.h"
#include <unistd.h>
#include <stdlib.h>
/**
 * change_directory - a function to handle the change of directory
 * @dir: destination directory
 * Return: (int)
 */
 char *home_dir;
char current_dir[MAX_COMMAND_LENGTH];
char new_dir[MAX_COMMAND_LENGTH];

int change_directory(char *dir)
{
        if (dir == NULL || _strcmp(dir, "~") == 0)
	{
                
                home_dir = getenv("HOME");
                if (home_dir == NULL)
                {
                        print_string("Error: Failed to get home directory\n");
                        return (-1);
                }
                dir = home_dir;
        }
	if (_strcmp(dir, "-") == 0)
	{
		dir = "..";
	}

        /*char current_dir[MAX_COMMAND_LENGTH];*/
        if (getcwd(current_dir, sizeof(current_dir)) == NULL)
        {
                print_string("Error: Failed to get current directory\n");
                return (-1);
        }

        if (chdir(dir) != 0)
        {
                print_string("Error: Failed to change directory\n");
                return (-1);
        }

       
        if (setenv("PWD", dir, 1) != 0)
        {
                print_string("Error: Failed to update PWD environment variable\n");
                return (-1);
        }

        
       /* char new_dir[MAX_COMMAND_LENGTH];*/
        if (getcwd(new_dir, sizeof(new_dir)) == NULL)
        {
                print_string("Error: Failed to get current directory\n");
                return (-1);
        }
        print_string(new_dir);
        print_string("\n");

        return (0);
}

