#include "shell.h"

/**
 * _eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Noting
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
 * _putfd - writes the character c to given fd
 * @c: The charcter to print
 * @fd: the filedescriptor to write to
 *
 * Return: on success 1.
 * On error, -1 is returned and errno is set appropriately
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];
	int j;

	if (c != BUF_FLUSH)
	{
		buf[i++] = c;
	}

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		while (j < i)
		{
			write(fd, &buf[j], 1);
			j++;
		}
		i = 0;
	}

	return (1);
}

/**
 * _putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write
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
