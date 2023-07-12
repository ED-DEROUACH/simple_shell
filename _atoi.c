#include "shell.h"
#include <stdlib.h>

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct adress
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	if (isatty(STDIN_FILENO) && info->readfd <= 2)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

