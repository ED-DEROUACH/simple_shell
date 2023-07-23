#include "shell.h"

/**
 * _erratoi - convert string to integers
 * @str: string
 * Return: 0 if string has no nb, -1 on fail, otherwise return converted number
 */
int _erratoi(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (0);
		i++;
	}
	return (result);
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
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (in < 0)
	{
		_abs_ = -in;
		__putchar('-');
		count++;
	}
	else
		_abs_ = in;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' +  current);
	count++;
	return (count);
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
	static char buffer[50];
	char sign = 0;
	char *p;
	unsigned long n = nb;

	if (!(f & CONVERT_UNSIGNED) && nb < 0)
	{
		n = -nb;
		sign = '-';
	}
	char *array = (f & CONVERT_LOWERCASE) ? "0123456789abcdef"
		: "0123456789ABCDEF";

	p = &buffer[49];
	*p = '\0';
	do {
		*--p = array[n % b];
		n /= b;
	} while (n != 0);
	if (sign)
		*--p = sign;
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
