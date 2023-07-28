#include "shell.h"

/**
 * get_environ - returns the string array
 * @info: Struct
 * Return: 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Struct
 * @v: string
 * Return: 1 on success, 0 otherwise
 */
int _unsetenv(info_t *info, char *v)
{
	list_t *nd = info->env;
	size_t j = 0;
	char *ptr;

	if (!nd || !v)
		return (0);

	while (nd)
	{
		ptr = starts_with(nd->str, v);

		if (ptr && *ptr == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), j);
			j = 0;
			nd = info->env;
			continue;
		}
		nd = nd->next;
		j++;
	}

	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment
 * @info: Struct
 * @v: string var
 * @val: the string value
 * Return: 0
 */
int _setenv(info_t *info, char *v, char *val)
{
	char *buffer = NULL;
	list_t *nd;
	char *ptr;

	if (!v || !val)
		return (0);

	buffer = malloc(_strlen(v) + _strlen(val) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, v);
	_strcat(buffer, "=");
	_strcat(buffer, val);
	nd = info->env;
	while (nd)
	{
		ptr = starts_with(nd->str, v);
		if (ptr && *ptr == '=')
		{
			free(nd->str);
			nd->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		nd = nd->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
