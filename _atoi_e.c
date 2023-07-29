#include "shell.h"
#include <stdlib.h>

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct
 *
 * Return: 1 if true, 0 otherwise
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
 * @ch: ch to check
 * @dlm: delim string
 * Return: 1 on success, 0 otherwise
 */
int is_delim(char ch, char *dlm)
{
	while (*dlm)
	{
		if (*dlm++ == ch)
			return (1);
	}
	return (0);
}

/**
 *_isalpha - checks if a ch is alphabet
 *@ch: char to test
 *Return: 1 success, 0 otherwise
 */

int _isalpha(int ch)
{
	return (((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) ? 1 : 0);
}

/**
 *_atoi - converts a string to int
 *@str: string to convert
 *Return: 0 for no nb, otherwise; resultat
 */

int _atoi(char *str)
{
	int x = 0, sg = 1, fg = 0, output;
	unsigned int res = 0;

	while (str[x] != '\0' && fg != 2)
	{
		if (str[x] == '-')
			sg *= -1;
		if (str[x] >= '0' && str[x] <= '9')
		{
			fg = 1;
			res *= 10;
			res += (str[x] - '0');
		}
		else if (fg == 1)
			fg = 2;
		x++;
	}
	if (sg == -1)
		output = -res;
	else
		output = res;
	return (output);

}
