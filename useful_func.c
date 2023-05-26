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
/**
 * intToStr -a funct that converts an int string
 * @num: the input number
 * @str: the input string
 * @size: size of string
 * Return: (void)
 */
void intToStr(int num, char *str, int size)
{
	int i = 0;
	int isNegative = 0;
	int len;

	if (num < 0)
	{
		isNegative = 1;
		num = -num;
	}
	if (size <= isNegative)
		return;
	while (num != 0)
	{
		int digit = num % 10;

		str[i++] = '0' + digit;
		num /= 10;
	}
	if (isNegative)
	{
		str[i++] = '-';
	}
	str[i] = '\0';
	len = i;
	for (i = 0; i < len / 2; i++)
	{
		char temp = str[i];

		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
	}
}
/**
 * my_sizeof_var -a function that mimick sizeof func
 * @object: the obj to eval the size
 * Return: size of object
 */
size_t my_sizeof_var(const void *object)
{
	const char *charPtr = (const char *)object;

	return (sizeof(*charPtr));
}
/**
 * _strncpy -a function that mimick strncpy
 * @dest: destination string
 * @src: source string
 * @n: number of char
 * Return: a pointer to string
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
	char *dest_start = dest;

	while (*src && n > 0)
	{
		*dest++ = *src++;
		n--;
	}
	while (n > 0)
	{
		*dest++ = '\0';
		n--;
	}
	return (dest_start);
}
