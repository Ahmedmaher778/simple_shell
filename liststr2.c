#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node.
 * Return: size of list.
*/

size_t list_len(const list_t *h)
{
	size_t l = 0;

	while (h)
	{
		h = h->next;
		l++;
	}
	return (l);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node.
 * Return: array of strings.
*/

char **list_to_strings(list_t *head)
{
	list_t *nod = head;
	char *st;
	char **sts;
	size_t l = list_len(head), k;

	if (!head || !l)
		return (NULL);
	sts = malloc(sizeof(char *) * (l + 1));
	if (!sts)
		return (NULL);
	for (l = 0; nod; nod = nod->next, l++)
	{
		st = malloc(_strlen(nod->st) + 1);
		if (!st)
		{
			for (k = 0; k < l; k++)
				free(sts[k]);
			free(sts);
			return (NULL);
		}

		st = _strcpy(st, nod->st);
		sts[l] = st;
	}
	sts[l] = NULL;
	return (sts);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 * Return: size of list
*/

size_t print_list(const list_t *h)
{
	size_t l = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		l++;
	}
	return (l);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: next character after prefix to match
 * Return: match node or null
*/

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *b = NULL;

	while (node)
	{
		b = starts_with(node->str, prefix);
		if (b && ((c == -1) || (*b == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 * Return: index of node or -1
*/

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t l = 0;

	while (head)
	{
		if (head == node)
			return (l);
		head = head->next;
		l++;
	}
	return (-1);
}

