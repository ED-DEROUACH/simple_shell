#include "shell.h"
#include <string.h>

/**
 **_strncpy - copies a string
 *@d: the destination string to be copied to
 *@sr: the source string
 *@by: the amount of char
 *Return: string
 */
char *_strncpy(char *d, char *sr, int by)
{
	int i, j;
	char *s = d;

	i = 0;
	while (sr[i] != '\0' && i < by - 1)
	{
		d[i] = sr[i];
		i++;
	}
	if (i < by)
	{
		j = i;
		while (j < by)
		{
			d[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@ds: the first string
 *@src: the second string
 *@nb: the amount of bytes to use
 *Return: string
 */
char *_strncat(char *ds, char *src, int nb)
{
	int i, j = 0;
	char *s = ds;

	for (i = 0; ds[i] != '\0'; i++)
		;
	for (j = 0; src[j] != '\0' && j < nb; j++)
	{
		ds[i] = src[j];
		i++;
	}
	if (j < nb)
		ds[i] = '\0';
	return (s);

}
/**
 **_strchr - locates a character in a string
 *@str: string
 *@ch: char
 *Return: a pointer
 */
char *_strchr(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');
	return (NULL);
}
