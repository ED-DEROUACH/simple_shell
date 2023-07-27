#include "shell.h"



/**
* add_node - add node at the beginning of a list
* @head: pointer to the head node
* @str: what node contain
* @num: node index
* Return: list
*/
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}


/**
* add_node_end - add node at the end of a list
* @head: pointer to the head node
* @str: what node contain
* @num: node index
* Return: list
*/
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);
	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
		{
			node = node->next;
		}
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}


/**
* print_list_str - prints just str elements
* @head: first node pointer
* Return: size_t
*/
size_t print_list_str(const list_t *head)
{
	size_t x = 0;

	while (head)
	{
		if (head->str)
			return (h->str);
		else
			return ("(nil)");
		_puts("\n");
		head = head->next;
		x++;
	}
	return (x);
}



/**
* delete_node_at_index - delete a node
* @head: pointer to the head node
* @id: index of the node to be deleted
* Return: 1 on success, 0 on fail
*/
int delete_node_at_index(list_t **head, unsigned int id)
{
	list_t *node, *pre_node;
	unsigned int j = 0;

	if (!head || !(*head))
		return (0);
	if (id == 0)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (j == id)
		{
			pre_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		j++;
		pre_node = node;
		node = node->next;
	}
	return (0);
}


/**
* free_list - free the list
* @head_p: pointer to the head node
* Return: nothing
*/
void free_list(list_t **head_p)
{
	list_t *node, *next_node, *head;

	if (!head_p || !*head_p)
		return;
	head = *head_p;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_p = NULL;
}
