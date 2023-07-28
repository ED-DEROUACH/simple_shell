#include "shell.h"

/**
 *_eputs - prints an input string
 * @s: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *s)
{
	int x;

	if (!str)
		return;

	for (x = 0; str[x] != '\0'; x++)
	{
		_eputchar(str[x]);
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @ch: char to print
 * Return: On success 1, -1 otherwise
 */
int _eputchar(char ch)
{
	static int x;
	static char buffer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buffer, x);
		i = 0;
	}

	if (ch != BUF_FLUSH)
	{
		buffer[i++] = ch;
	}

	return (1);
}
/**
 * _putfd - writes the char
 * @ch: The char to print
 * @fdesc: The file to write in
 * Return: On success 1. -1 otherwise
 */
int _putfd(char ch, int fdesc)
{
	static int x;
	static char buffer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(fdesc, buffer, x);
		x = 0;
	}
	if (ch != BUF_FLUSH)
		buffer[x++] = ch;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @s: the string to be printed
 * @fdesc: the filedescriptor to write to
 * Return: the number of chars put
 */

int _putsfd(char *s, int fdesc)
{
	int x = 0;

	if (!s)
		return (0);
	while (*s)
	{
		x += _putfd(*s++, fdesc);
	}
	return (x);
}
