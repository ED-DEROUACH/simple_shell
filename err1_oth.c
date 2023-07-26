#include "shell.h"

/**
 * _erratoi - converts to int
 * @s: the string
 * Return: 0 when no nb exist,  -1 for error, converted number otherwise
 */
int _erratoi(char *s)
{
	int j = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;   
	for (j = 0;  s[j] != '\0'; j++)
	{
		if (s[j] >= '0' && s[j] <= '9')
		{
			res *= 10;
			res += (s[j] - '0');
			if(res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);  
}

/**
 * print_error - prints err msg
 * @info: sturuct
 * @es: string with specified error 
 * Return: 0 if no nb exist, 1 for err, the rusult otherwise
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function prints a decimal
 * @input: input
 * @fd: the file
 *
 * Return: number of char
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, c = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		c++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			c++;
		}
		current %= j;
	}
	__putchar('0' + current);
	c++;

	return (c);
}

/**
 * convert_number - converter a function
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces '#' with '\0'
 * @buf: addres to modify
 *
 * Return: 0;
 */
void remove_comments(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
}
