#include "shell.h"
#include <string.h>

/**
 **_memset - fills memory with a constant byte
 *@str: pointer to memory
 *@by: bytes
 *@nb: amount of bytes
 *Return: pointer
 */
char *_memset(char *str, char by, unsigned int nb)
{
	unsigned int x = 0;

	while (x < nb)
	{
		str[x] = by;
		x++;
	}
	return (str);
}

/**
 * ffree - frees a string of strings
 * @sos: string of strings
 */
void ffree(char **sos)
{
	char **temp = sos;

	if (!sos)
		return;

	while (*sos)
	{
		free(*sos++);
	}

	free(temp);
}

/**
 * _realloc - reallocates a block of memory
 * @q: pointer to previous malloc'ated block
 * @o_s: byte size of previous block
 * @n_s: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *q, unsigned int o_s, unsigned int n_s)
{
	char *ptr;

	if (!q)
		return (malloc(n_s));
	if (!n_s)
	{
		return (free(q), NULL);
	}
	if (n_s == o_s)
		return (q);
	ptr = malloc(n_s);
	if (!ptr)
		return (NULL);
	o_s = o_s < n_s ? o_s : n_s;
	while (o_s--)
		ptr[o_s] = ((char *)q)[o_s];
	free(q);
	return (ptr);
}
