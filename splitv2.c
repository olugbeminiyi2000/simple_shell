#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGUMENTS 10

/**
 * split_by_separator - Split command by ';' separator
 * @command: The command to split
 * @commands: Array to store the split commands
 * @separator: The separator character
 * Return: The number of split commands
 */
int split_by_separator(const char *command, char **commands, char separator)
{
    char *copy = strdup(command);
    char *token = strtok(copy, &separator);
    int num_commands = 0;

    while (token != NULL && num_commands < MAX_ARGUMENTS)
    {
        commands[num_commands++] = strdup(token);
        token = strtok(NULL, &separator);
    }

    free(copy);
    return num_commands;
}

/**
 * split_by_operators - Split command by '&&' and '||' operators
 * @command: The command to split
 * @commands: Array to store the split commands
 * Return: The number of split commands
 */
int split_by_operators(const char *command, char **commands)
{
    const char *operators = "&&||";
    char *copy = strdup(command);
    char *token = strtok(copy, operators);
    int num_commands = 0;

    while (token != NULL && num_commands < MAX_ARGUMENTS)
    {
        commands[num_commands++] = strdup(token);
        token = strtok(NULL, operators);
    }

    free(copy);
    return num_commands;
}

