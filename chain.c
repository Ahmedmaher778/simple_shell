#include "shell.h"

/**
 * is_chain - check if the char is a chain delimeter
 * @info: the structure parameter
 * @buf: buffer char
 * @p: address
 *
 * Return: if chain delimeter return 1, otherwise 0
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t x = *p;

	if (buf[x] == '|' && buf[x + 1] == '|')
	{
		buf[x] = 0;
		x++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[x] == '&' && buf[x + 1] == '&')
	{
		buf[x] = 0;
		x++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[x] == ';') /* found end of this command */
	{
		buf[x] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
	{
		return (0);
	}

	*p = x;
	return (1);
}

/**
 * check_chain - based on last status checks if we continue chaining
 * @info: the structre parameter
 * @buf: buffer char
 * @p: address
 * @i: beginning position
 * @len: the length
 *
 * Return: no return (void)
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t x = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			x = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			x = len;
		}
	}

	*p = x;
}


/**
 * replace_alias - replaces aliases
 * @info: the structure parameter
 *
 * Return: replaced return 1, otherwise 0
 */
int replace_alias(info_t *info)
{
	int x;
	list_t *node;
	char *p;

	for (x = 0; x < 10; x++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (node == NULL)
		{
			return (0);
		}
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (p == NULL)
		{
			return (0);
		}
		p = _strdup(p + 1);
		if (p == NULL)
		{
			return (0);
		}

		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars
 * @info: the structure parameter
 *
 * Return: replaced return 1, otherwise 0
 */
int replace_vars(info_t *info)
{
	int x = 0;
	list_t *node;

	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;

		if (!_strcmp(info->argv[x], "$?"))
		{
			replace_string(&(info->argv[x]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[x], "$$"))
		{
			replace_string(&(info->argv[x]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[x][1], '=');
		if (node)
		{
			replace_string(&(info->argv[x]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[x], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address
 * @new: string
 *
 * Return: replaced return 1, otherwise 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
