#include "shell.h"

/**
 * bfree - free a pointer and put NULL in it's address
 * @p: address of the pointer
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
