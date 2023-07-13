#include "shell.h"

/**
 * _myenv - display the environment
 * @info: struct
 * Return: 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - find the value of the environ
 * @info: struct
 * @nm: the var name
 * Return: the value on success, NULL otherwise
 */
char *_getenv(info_t *info, const char *nm)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, nm);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - set a new environment
 * @info: struct
 * Return: 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("wrong number of args\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - remove a variable of environment
 * @info: struct
 * Return: 0
 */
int _myunsetenv(info_t *info)
{
	int x, i = 1;

	if (info->argc == 1)
	{
		_eputs("not too many args.\n");
		return (1);
	}
	while (i <= info->argc)
	{
		_unsetenv(info, info->argv[i]);
		i++;
	}
	return (0);
}

/**
 * populate_env_list - populate the env argument
 * @info: struct
 * Return: 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	i = 0;
	while (environ[i])
	{
		add_node__end(&node, environ[1], 0);
		i++;
	}
	info->env = node;
	return (0);
}
