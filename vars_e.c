#include "shell.h"
#include <stdio.h>

/**
 * is_chain - test if current char is delim
 * @info: struct
 * @buffer: the buffer
 * @ptr: address
 * Return: 1 on success, 0 otherwise
 */
int is_chain(info_t *info, char *buffer, size_t *ptr)
{
	size_t x = *ptr;

	if (buffer[x] == '|' && buffer[x + 1] == '|')
	{
		buffer[x] = 0;
		x++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[x] == '&' && buffer[x + 1] == '&')
	{
		buffer[x] = 0;
		x++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[x] == ';')
	{
		buffer[x] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = x;
	return (1);
}

/**
 * check_chain - test the chaining
 * @info: struct
 * @buffer: the buffer
 * @ptr: address
 * @id: the first position in buf
 * @l: length of buffer
 * Return: Void
 */
void check_chain(info_t *info, char *buffer, size_t *ptr, size_t id, size_t l)
{
	size_t x = *ptr;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[id] = 0;
			x = l;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[id] = 0;
			x = l;
		}
	}
	*ptr = x;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info:  struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int x = 0;
	char *ptr;
	list_t *nd;

	while (x < 10)
	{
		nd = node_starts_with(info->alias, info->argv[0], '=');
		if (!nd)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(nd->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
		x++;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in string that is tokenized
 * @info: struct
 * Return: 1 on success, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int x = 0;
	list_t *nd;

	while (info->argv[x])
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;

		if (!_strcmp(info->argv[x], "$?"))
		{
			replace_string(&(info->argv[x]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[x], "$$"))
		{
			replace_string(&(info->argv[x]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nd = node_starts_with(info->env, &info->argv[x][1], '=');
		if (nd)
		{
			replace_string(&(info->argv[x]),
				_strdup(_strchr(nd->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[x], _strdup(""));
		x++;
	}
	return (0);
}

/**
 * replace_string - replaces string
 * @o_s: address of old string
 * @n_s: new string
 * Return: 1 on success, 0 otherwise
 */
int replace_string(char **o_s, char *n_s)
{
	free(*o_s);
	*o_s = n_s;
	return (1);
}
