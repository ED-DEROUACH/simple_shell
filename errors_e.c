#include "shell.h"

/**
 *_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i;

	if (!str)
		return;

	for (i = 0; str[i] != '\0'; i++)
	{
		_eputchar(str[i]);
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];
	int j;

	if (c != BUF_FLUSH)
	{
		buf[i] = c;
		i++;
	}

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		for (j = i - 1; j >= 0; j--)
		{
			write(2, &buf[j], 1);
		}
		i = 0;
	}

	return (1);
}
/**
 * _putfd - writes the char
 * @ch: The char to print
 * @fdesc: The file to write in
 *
 * Return: On success 1. otherwise -1 is returned
 */
int _putfd(char ch, int fdesc)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fdesc, buf, j);
		j = 0;
	}
	if (ch != BUF_FLUSH)
		buf[j++] = ch;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */

int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
