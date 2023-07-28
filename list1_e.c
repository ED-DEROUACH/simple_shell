#include "shell.h"

/**
 * list_len - determines length of linked list
 * @p_n: ptr to first node
 * Return: size of the list
 */
size_t list_len(const list_t *p_n)
{
	size_t x = 0;

	while (p_n)
	{
		p_n = p_n->next;
		x++;
	}
	return (x);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *nd = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	i = 0;
	while (nd)
	{
		str = malloc(_strlen(nd->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, nd->str);
		strs[i] = str;
		nd = nd->next;
		i++;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @head: pointer to first node
 * Return: size of the list
 */
size_t print_list(const list_t *head)
{
	size_t x = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		x++;
	}
	return (x);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @nd: pointer to list head
 * @pre: string to match
 * @ch: next char
 * Return: the node on success, null otherwise
 */
list_t *node_starts_with(list_t *nd, char *pre, char ch)
{
	char *ptr = NULL;

	while (nd)
	{
		ptr = starts_with(nd->str, pre);
		if (ptr && ((ch == -1) || (*ptr == ch)))
			return (nd);
		nd = nd->next;
	}

	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @h: pointer to list head
 * @nd: pointer to the node
 * Return: index of node, -1 otherwise
 */
ssize_t get_node_index(list_t *h, list_t *nd)
{
	size_t j = 0;

	while (h)
	{
		if (h == nd)
			return (j);
		h = h->next;
		j++;
	}
	return (-1);
}
