#include "shell.h"


/**
*_myenv - display the environment
*@info: struct
*Return: 0
*/
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
*_getenv - find the value of the environ
*@info: struct
*@nm: the var name
*Return: the value on success , NULL otherwise
*/
char *_getenv(info_t *info, const char *nm)
{
	list_t *nd = info->env;
	char *ptr;

	while (nd)
	{
		ptr = starts_with(nd->str, nm);
		if (ptr && *ptr)
			return (ptr);
		nd = nd->next;
	}
	return (NULL);
}


/**
*_mysetenv - set a new environment
*@info: struct
*Return: 0
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
*_myunsetenv - remove a variable of environment
*@info: struct
*Return: 0
*/
int _myunsetenv(info_t *info)
{
	int x;

	if (info->argc == 1)
	{
		_eputs("too few args.\n");
		return (1);
	}
	for (x = 1; x <= info->argc; x++)
		_unsetenv(info, info->argv[x]);
	return (0);
}


/**
*populate_env_list - poputale the env argument
*@info: struct
*Return: 0
*/
int populate_env_list(info_t *info)
{
	list_t *nd = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
	{
		add_node_end(&nd, environ[x], 0);
	}
	info->env = nd;
	return (0);
}
