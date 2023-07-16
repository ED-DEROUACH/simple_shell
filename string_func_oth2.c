#include "shell.h"

/**
 * strtow1 - splites a string into words
 * @s: string
 * @del: delimeter
 * Return: a pointer or NULL on fail
 */
char **strtow1(char *s, char *del)
{
	int i, j, k = 0, m, nw = 0;
	char **str;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (del == NULL)
		del = " ";
	for (i = 0; s[i] != '\0'; i++)
	{
		if (!is_delim(s[i], del) && (is_delim(s[i + 1], del) || !s[i + 1]))
			nw++;
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
		while (!is_delim(s[i + k], del) && s[i + k] != '\0')
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
		str[j][m] = '\0';
	}
	str[j] = NULL;
	return (str);
}

/**
 * strtow2 - splites a string
 * @s: string
 * @dlm: delimiter
 * Return: a pointer to a string
 */
char **strtow2(char *s, char dlm)
{
	int i = 0, j, k, m, nw = 0;
	char **str;

	if (s == NULL || s[0] == '\0')
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != dlm && (s[i + 1] == dlm || !s[i + 1]) || s[i + 1] == dlm)
			nw++;
		i++;
	}
	if (nw == 0)
		return (NULL);
	str = malloc((nw + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	for (j = 0; j < nw; j++)
	{
		for (i = 0; s[i] == dlm; i++)
			;
		k = 0;
		while (s[i + k] != dlm && s[i + k] && s[i + k] != dlm)
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
		str[j][m] = '\0';
	}
	str[j] = NULL;
	return (str);
}
