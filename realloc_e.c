#include "shell.h"
#include <string.h>

/**
 **_memset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
return ((char *)memset(s, b, n));
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
char **temp = pp;

if (!pp)
return;


while (*pp)
{
free(*pp);
pp++;
}

free(temp);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
if (!ptr)
return (malloc(new_size));
if (!new_size)
{
free(ptr);
return (NULL);
}
if (new_size == old_size)
return (ptr);

void *p = malloc(new_size);
if (!p)
return (NULL);

memcpy(p, ptr, (old_size < new_size) ? old_size : new_size);
free(ptr);

return (p);
}
