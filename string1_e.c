#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: source
 * Return: pointer
 */
char *_strcpy(char *dest, char *src)
{
	int x = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[x])
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = '\0';
	return (dest);

}

/**
 * _strdup - duplicates a string
 * @s: string
 * Return: pointer
 */
char *_strdup(const char *s)
{
	int l = 0;
	char *r;

	if (s == NULL)
		return (NULL);
	while (*s++)
	{
		l++;
	}
	r = malloc(sizeof(char) * (l + 1));
	if (!r)
		return (NULL);
	for (l++; l--;)
	{
		r[l] = *--s;
	}
	return (r);
}

/**
 *_puts - prints an input string
 *@s: the string to be printed
 * Return: Nothing
 */
void _puts(char *s)
{
	int x;

	if (!s)
		return;
	for (x = 0; s[x] != '\0'; x++)
	{
		_putchar(s[x]);
	}
}

/**
 * _putchar - writes the character c to stdout
 * @ch: char to print
 * Return: On success 1, -1 otherwise
 */
int _putchar(char ch)
{
	static int x;
	static char buffer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buffer, x);
		x = 0;
	}
	if (ch != BUF_FLUSH)
	{
		buffer[x++] = ch;
	}

	return (1);
}
