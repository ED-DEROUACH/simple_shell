#include "shell.h"
#include <stdlib.h>

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct adress
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	if (isatty(STDIN_FILENO) && info->readfd <= 2)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * is_delim - checks if character is a delimeter
 * @c :the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	return ((strchr(delim, c) != NULL) ? 1 : 0);
}

/**
 * _isalpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
	return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? 1 : 0);
}

/**
 * _atoi - converts a string to an intger
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	return (atoi(s));
}
