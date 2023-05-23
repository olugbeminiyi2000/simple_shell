#include "main.h"
/**
 * _strlen -a function to calculate the lenght of a string
 * @str: the input string
 * Return: the lenght of the string
 */
size_t _strlen(const char *str)
{
	const char *s = str;

	while (*s)
	{
		s++;
	}
	return ((size_t)(s - str));
}

/**
 * _strcmp -a function that compare the ASIC cod of two strings
 * @str1: first string to compare
 * @str2: second strig to compare
 * Return: an int
 */
int _strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
