#include "shell.h"

/**
 * add_node - adds a node to the start list
 * @head: address
 * @str: str field
 * @num: node index
 *
 * Return: the list size
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_h;

	if (!head){
		return (NULL);
    }
	new_h = malloc(sizeof(list_t));
	if (!new_h){
		return (NULL);
    }
	_memset((void *)new_h, 0, sizeof(list_t));
	new_h->num = num;
	if (str)
	{
		new_h->str = _strdup(str);
		if (!new_h->str)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->next = *head;
	*head = new_h;
	return (new_h);
}

/**
 * add_node_end - adds a node to the end list
 * @head: address
 * @str: str field
 * @num: node index
 *
 * Return: list size
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_n, *nuh;

	if (!head)
		return (NULL);

	nuh = *head;
	new_n = malloc(sizeof(list_t));
	if (!new_n)
		return (NULL);
	_memset((void *)new_n, 0, sizeof(list_t));
	new_n->num = num;
	if (str)
	{
		new_n->str = _strdup(str);
		if (!new_n->str)
		{
			free(new_n);
			return (NULL);
		}
	}
	if (nuh)
	{
		while (nuh->next)
			nuh = nuh->next;
		nuh->next = new_n;
	}
	else
		*head = new_n;
	return (new_n);
}

/**
 * print_list_str - print_list_str function
 * @h: is a pointer
 *
 * Return: list size
 */
size_t print_list_str(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		x++;
	}
	return (x);
}

/**
 * delete_node_at_index - deletes node
 * @head: is a address
 * @index: is a index of node
 *
 * Return: on success 1, otherwise 0
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *nuh, *previous_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		nuh = *head;
		*head = (*head)->next;
		free(nuh->str);
		free(nuh);
		return (1);
	}
	nuh = *head;
	while (nuh)
	{
		if (i == index)
		{
			previous_node->next = nuh->next;
			free(nuh->str);
			free(nuh);
			return (1);
		}
		i++;
		previous_node = nuh;
		nuh = nuh->next;
	}
	return (0);
}

/**
 * free_list - frees all the list nodes
 * @head_ptr: address
 *
 * Return: no return (void)
 */
void free_list(list_t **head_ptr)
{
	list_t *nuh, *next_nuh, *h;

	if (!head_ptr || !*head_ptr)
		return;
	h = *head_ptr;
	nuh = h;
	while (nuh)
	{
		next_nuh = nuh->next;
		free(nuh->str);
		free(nuh);
		nuh = next_nuh;
	}
	*head_ptr = NULL;
}
