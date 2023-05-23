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
// Function to convert an integer to a string
void intToStr(int num, char* str, int size) {
    int i = 0;
    int isNegative = 0;

    // Handle negative numbers
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    // Convert each digit to a character in reverse order
    while (num != 0) {
        int digit = num % 10;
        str[i++] = '0' + digit;
        num /= 10;
    }

    // Add the negative sign if necessary
    if (isNegative) {
        str[i++] = '-';
    }

    // Add null terminator at the end
    str[i] = '\0';

    // Reverse the string
    int len = i;
    for (i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}
size_t my_sizeof_var(const void* object) {
    return (size_t)(*(char(*)[1])object - *(char(*)[0])object);
}
