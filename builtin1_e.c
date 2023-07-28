#include "shell.h"

/**
 * _myhistory - displays the history list
 * @info: Struct
 * Return: integer
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: struct
 * @s: string
 * Return: 0 on success, 1 otherwise
 */
int unset_alias(info_t *info, char *s)
{
	char *p ,c;
	int r;

	p = _strchr(s, '=');
	if (!p)
		return (1);

	c = *p;
	*p = 0;

	r = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, s, -1)));
	*p = c;

	return (r);
}

/**
 * set_alias - sets alias to string
 * @info: struct
 * @s: string
 * Return: 0 on success, 1 otherwise
 */
int set_alias(info_t *info, char *s)
{
	char *ptr = _strchr(s, '=');
	int r;

	if (!ptr)
		return (1);
	if (!*++ptr)
	{
		r = unset_alias(info, s);
		return (r);
	}
	unset_alias(info, s);

	return (add_node_end(&(info->alias), s, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @nd: the alias node
 * Return: 0 on success, 1 otherwise
 */
int print_alias(list_t *nd)
{
	char *ptr = NULL, *m = NULL;

	if (nd)
	{
		ptr = _strchr(nd->str, '=');
		m = nd->str;

		while (m <= ptr)
			m++;
		_putchar(*m);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");

		return (0);
	}

	return (1);
}

/**
 * _myalias - mimics the alias
 * @info: Struct
 * Return: 0
 */
int _myalias(info_t *info)
{
	int j = 1;
	char *ptr = NULL;
	list_t *nd = NULL;

	if (info->argc == 1)
	{
		nd = info->alias;

		while (nd)
		{
			print_alias(nd);
			nd = nd->next;
		}

		return (0);
	}

	while (info->argv[j])
	{
		ptr = _strchr(info->argv[j], '=');

		if (ptr)
			set_alias(info, info->argv[j]);
		else
			print_alias(node_starts_with(info->alias, info->argv[j], '='));

		j++;
	}

	return (0);
}
