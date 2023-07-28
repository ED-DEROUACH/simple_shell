#include "shell.h"

/**
 * hsh - main shell loop
 * @info: struct
 * @av: argument vector
 * Return: 0 on success, if error -1, otherwise integer
 */
int hsh(info_t *info, char **av)
{
	ssize_t re = 0;
	int b_ret = 0;

	while (re != -1 && b_ret != -1)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		re = get_input(info);
		if (re != -1)
		{
			set_info(info, av);
			b_ret = find_builtin(info);
			if (b_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}

	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (b_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (b_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: struct
 * Return: -1 if builtin not found,
 */
int find_builtin(info_t *info)
{
	int x = 0;
	int built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	while (builtintbl[x].type)
	{
		if (_strcmp(info->argv[0], builtintbl[x].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[x].func(info);
			break;
		}
		x++;
	}

	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: struct
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i = 0, k = 0;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	while (info->arg[i])
	{
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
		i++;
	}

	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=") || info->
					argv[0][0] == '/') && is_cmd(info, info->argv[0]))
		fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: struct
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
