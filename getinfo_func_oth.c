#include "shell.h"

/**
* clear_info - initializes all the struct info_t types with null
* @info: address of the struct
* Return: nothing
*/
void clear_info(info_t *info)
{
	if (!info)
		return;

	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
* set_info - initializes the struct info_t
* @info: address the address
* @av: argument vector
* Return: nothing
*/
void set_info(info_t *info, char **av)
{
	int i;

	if (!info || !av)
		return;

	info->fname = av[0];
	if (info->arg){
		info->argv = _strtow(info->arg, "\t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
* free_info - free the struct
* @info: the address of the struct
* @tr: true when the struct is freed
* Return: nothing
*/
void free_info(info_t *info, int tr)
{
	if (!info)
		return;

	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (tr){
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}


