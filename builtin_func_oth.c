#include "shell.h"
/**
* _myexit - leave the shell
* @inf: struct
* Return: integer
*/
int _myexit(info_t *inf)
{
	int exittest;

	if (inf->argv[1])
	{
		exittest = _erratoi(inf->argv[1]);
		if (exittest == -1)
		{
			inf->status = 2;
			print_error(inf, "unallowed nmb");
			_eputs(inf->argv[1]);
			_eputchar('\n');
			return (1);
		}
		inf->err_num = _erratoi(inf->argv[1]);
		return (-1);
	}
	inf->err_num = -1;
	return (-2);
}

/**
* _mycd - change the dire
* @inf: struct
* Return: 0
*/
int _mycd(info_t *inf)
{
	char *s, *d, buf[1024];
	int dir_ret;

	s = getcwd(buf, 1024);
	if (!s)
		_puts("TODO:>>getcwd fail error msg\n");
	if (!inf->argv[1])
	{
		d = _getenv(inf, "HOME = ");
		if (!d)
			dir_ret = chdir((_getenv(inf, "PWD=")) ? d : "/");
		else
			dir_ret = chdir(d);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!_getenv(inf, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inf, "OLDPWD=")), putchar('\n');
		dir_ret = chdir((d = _getenv(inf, "OLDPWD=")) ? d : "/");
	}
	else
		dir_ret = chdir(inf->argv[1]);
	if (dir_ret == -1)
	{
		print_error(inf, "can not use cd");
		_eputs(inf->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
		_setenv(inf, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
* _myhelp - change the dir
* @inf: struct
* Return: 0
*/
int _myhelp(info_t *inf)
{
	char **a_array;

	a_array = inf->argv;
	_puts("Help the call work\n");
	if (0)
		_puts(*a_array);
	return (0);
}
