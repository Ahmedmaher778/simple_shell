#include "shell.h"

/**
 * _myhistory - displays history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments.
 *  Return: Always 0
*/

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct.
 * @str: string alias
 * Return: Always 0 success, 1 on error.
*/

int unset_alias(info_t *info, char *str)
{
	char *b, x;
	int re;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	x = *b;
	*b = 0;
	re = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*b = x;
	return (re);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct.
 * @str: string alias
 * Return: Always 0 success, 1 on error.
*/

int set_alias(info_t *info, char *str)
{
	char *b;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	if (!*++b)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: alias node
 * Return: Always 0 success, 1 on error.
*/

int print_alias(list_t *node)
{
	char *b = NULL, *s = NULL;

	if (node)
	{
		b = _strchr(node->str, '=');
		for (s = node->str; s <= b; s++)
			_putchar(*s);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments
 *  Return: Always 0.
*/

int _myalias(info_t *info)
{
	int l = 0;
	char *b = NULL;
	list_t *nod = NULL;

	if (info->argc == 1)
	{
		nod = info->alias;
		while (nod)
		{
			print_alias(nod);
			nod = nod->next;
		}
		return (0);
	}
	for (l = 1; info->argv[l]; l++)
	{
		b = _strchr(info->argv[l], '=');
		if (b)
			set_alias(info, info->argv[l]);
		else
			print_alias(node_starts_with(info->alias, info->argv[l], '='));
	}

	return (0);
}
