#include "shell.h"

/**
* **strtow - splites a string into words
* @s: string
* @del: delimeter
* Return: a pointer or NULL on fail
*/
char **strtow(char *s, char *del)
{
	int i = 0, j, k, m, nw = 0;
	char **str;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	while (s[i] != '\0')
	{
		if (!is_delim(s[i], del) && (is_delim(s[i + 1], del) || !s[i + 1]))
			nw++;
		i++;
	}
	if (nw == 0)
		return (NULL);
	str = malloc((nw + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	for (i = 0, j = 0; j < nw; j++)
	{
		while (is_delim(s[i], del))
			i++;
		k = 0;
		while (!is_delim(s[i + k], del) && s[i + k])
			k++;
		str[j] = malloc((k + 1) * sizeof(char));
		if (!str[j])
		{
			for (k = 0; k < j; k++)
				free(str[k]);
			free(str);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			str[j][m] = s[i++];
		str[j][m] = 0;
	}
	str[j] = NULL;
	return (str);
}


/**
* **strtow2 - splites a string
* @str: string
* @del: delimeter
* Return: a pointer to a string
*/
char **strtow2(char *str, char del)
{
	int i, j, k, m, nw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] != del && str[i + 1] == del) ||
			(str[i] != del && !str[i + 1]) || str[i + 1] == del)
			nw++;
	}
	if (nw == 0)
		return (NULL);
	s = malloc((nw + 1) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < nw; j++)
	{
		while (str[i] == del && str[i] != del)
			i++;
		k = 0;
		while (str[i + k] != del && str[i + k] && str[i + k] != del)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
