#include "shell.h"

/**
 * _myexit - get out from the shell
 * @info: struct of potential arguments
 * Return: exits with an exit status
 */
int _myexit(info_t *info)
{
	int exittest;

	if (info->argv[1])
	{
		exittest = _erratoi(info->argv[1]);
		if (exittest == -1)
		{
			info->status = 2;
			print_error(info, "wrong number:");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - change the directory
 * @info: struct of arguments
 * Return: 0
 */
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int dir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO:>>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			dir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		dir_ret = chdir(info->argv[1]);
	if (dir_ret == -1)
	{
		print_error(info, "can't cd to");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - change the current directory
 * @info: struct
 * Return: 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call.\n");
	if (0)
		_puts(*arg_array);
	return (0);
}
