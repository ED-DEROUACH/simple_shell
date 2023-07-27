#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
return (strcpy(dest, src));
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
if (str == NULL)
return (NULL);

return (strdup(str));
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
if (str == NULL)
return;

printf("%s", str);
fflush(stdout);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	for (;;)
	{
		if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
		{
			if (write(1, buf, i) == -1)
				return (-1);
			i = 0;
			break;
		}
		else
		{
			buf[i++] = c;
		}
	}
	return (1);
}
