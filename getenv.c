#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	char **environ = info->environ;

	if (!environ || info->env_changed)
	{
		environ = list_to_strings(info->env);
		info->environ = environ;
		info->env_changed = 0;
	}

	return (environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;

	if (!node || !var)
		return (0);

	for (; node; node = node->next, i++)
	{
		char *p = starts_with(node->str, var);

		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
		}
	}

	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *
 * @info: Structure containing potential arguments.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;
	int env_changed = 0;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);

	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);

	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			env_changed = 1;
			free(buf);
			break;
		}
		node = node->next;
	}

	if (!node)
	{
		add_node_end(&(info->env), buf, 0);
		free(buf);
		env_changed = 1;
	}

	info->env_changed = env_changed;
	return (0);
}
