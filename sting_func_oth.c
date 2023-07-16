#include "shell.h"

/**
 * _strlen - return the string's length
 * @str: the main string
 * Return: int
 */
int _strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str++)
	{
		i++;
	}
	return (i);
}

/**
 * _strcmp - compare two strings
 * @str1: string 1
 * @str2: string 2
 * Return: -1 if str1 < str2, 1 if str1 > str2, 0 if str1 == str2
 */
int _strcmp(char *str1, char str2)
{
	while (*str1 && str2)
	{
		if (*str1 != str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else if (*str1 < *str2)
		return (-1);
	else
		return (1);
}

/**
 * starts_with - checks if a string begins with a given subtring
 * @str: the main string
 * @substr: the given string to search
 * Return: adress of the next char of the string or NULL
 */
char *starts_with(const char *str, const char *substr)
{
	while (*substr)
	{
		if (*substr++ != *str++)
			return (NULL);
	}
	return ((char *)str);
}

/**
 * _strcat - concatenates two strings
 * @new_str: the new string
 * @str: the firt string
 * Return: pointer to the new string
 */
char *_strcat(char *new_str, char *str)
{
	char *x = new_str;

	while (*new_str)
	{
		new_str++;
	}
	while (*str)
	{
		*new_str++ = *str++;
	}
	*new_str = '\0';
	return (x);
}
