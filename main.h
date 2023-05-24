#ifndef MAIN_H
#define MAIN_H
#include <stddef.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

void print_string(const char *str);
void read_input(char *buffer, size_t size);
void parse_arguments(const char *command, char **args, int *num_args);
int is_exit_command(const char *command);
int is_env_command(const char *command);
int is_cd_command(const char *command);
int execute_command(char **args);
void print_environment(void);
int change_directory(char *dir);
size_t  _strlen(const char *str);
int _strcmp(const char *str1, const char *str2);
void intToStr(int num, char* str, int size);
size_t my_sizeof_var(const void* object);
#endif
