#include "shell.h"

/**
* _strlen - returns the length of a string
* @str: the main string
* Return: int
*/
int _strlen(char *str)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str++)
	{
		j++;
	}
	return (j);
}



/**
* _strcmp - compare two strings
* @str1: string 1
* @str2: string 2
* Return: -1 if str1 < str2, 1 if str1 > str2, 0 if str1 == str2
*/
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else if (*str1 < *str2)
		return (-1);
	else
		return (1);
}



/**
* starts_with - checks if string begings with a given substring
* @stack: string to search
* @need: substring to find
* Return: address of next char of the string or NULL
*/
char *starts_with(const char *stack, const char *need)
{
	while (*need)
	{
		if (*need++ != *stack++)
			return (NULL);
	}
	return ((char *)stack);
}



/**
* _strcat - concatenates two strings
* @d: the destination
* @sr: the source
* Return: pointer to the destination
*/
char *_strcat(char *d, char *sr)
{
	char *rt = d;

	while (*d)
		d++;
	while (*sr)
		*d++ = *sr++;
	*d = *sr;
	return (rt);
}
