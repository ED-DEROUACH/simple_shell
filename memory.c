#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: adress of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	return ((ptr && *ptr) ? (free(*ptr), *ptr = NULL, 1) : 0);
}