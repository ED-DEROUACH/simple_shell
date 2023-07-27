#include "shell.h"


/**
* _erratoi - convert strings to integers
* @str: string
* Return: 0 if string has no nb, -1 on fail, otherwise return converted number
*/
int _erratoi(char *str)
{
	int j = 0;
	unsigned long int r = 0;

	if (*str == '+')
		str++;
	while (str[j] != '\0')
	{
		if (str[j] >= '0' && str[j] <= '9')
		{
			r *= 10;
			r += (str[j] - '0');
			if (r > INT_MAX)
				return (-1);
		}
		else
			return (0);
		j++;
	}
	return (r);
}


/**
* print_error - display an error message
* @info: struct
* @es: string with a specific error
* Return: nothing
*/
void print_error(info_t *info, char *es)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(es);
}


/**
* print_d - prints an integer in base 10
* @in: input
* @fd: where to write
* Return: decimal
*/
int print_d(int in, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j = 1000000000;
	int cmt = 0;
	unsigned int _abs_, cur;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (in < 0)
	{
		_abs_ = -in;
		__putchar('-');
		cmt++;
	}
	else
		_abs_ = in;
	cur = _abs_;
	while (j > 1)
	{
		if (_abs_ / j)
		{
			__putchar('0' + cur / j);
			cmt++;
		}
		cur %= j;
		j /= 10;
	}
	__putchar('0' + cur);
	cmt++;
	return (cmt);
}


/**
* convert_number - convert a number
* @nb: number
* @b: base
* @f: flages
* Return: string
*/
char *convert_number(long int nb, int b, int f)
{
	static char *array;
	static char buff[50];
	char sg = 0;
	char *p;
	unsigned long n = nb;

	if (!(f & CONVERT_UNSIGNED) && nb < 0)
	{
		n = -nb;
		sg = '-';
	}
	array = (f & CONVERT_LOWERCASE) ? "0123456789abcdef" :
		"0123456789ABCDEF";
	p = &buff[49];
	*p = '\0';
	do {
		*--p = array[n % b];
		n /= b;
	} while (n != 0);
	if (sg)
		*--p = sg;
	return (p);
}


/**
* remove_comments - replace '#' with '\0'
* @b: the address of the string
* Return: nothing
*/
void remove_comments(char *b)
{
	int j = 0;

	while (b[j] != '\0')
	{
		if (b[j] == '#' && (j == 0 || b[j - 1] == ' '))
		{
			b[j] = '\0';
			break;
		}
		j++;
	}
}
