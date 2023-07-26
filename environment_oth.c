#include "shell.h"

/**
 * _myenv - prints the environment
 * @info: Struct
 * Return: 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - print the value of environ 
 * @info: Struct
 * @name: env var nm
 *
 * Return: value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = starts_with(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - set new enviro var
 * @info: Struct
 *  Return: 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("incorrect nb of args\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - strip an environ var
 * @info: Struct
 *  Return: 0
 */
int _myunsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_eputs("Not too many args\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		_unsetenv(info, info->argv[j]);

	return (0);
}

/**
 * populate_env_list - populates a linked list
 * @info: Struct
 * Return: 0
 */
int populate_env_list(info_t *info)
{
	list_t *nd = NULL;
	size_t j; 

	for(j = 0; environ[j]; j++)
		add_node_end(&nd, environ[j], 0);
	info->env = nd;
	return (0); 
}
