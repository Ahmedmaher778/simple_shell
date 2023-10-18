#include "shell.h"

/**
 * hsh - main shell
 * @info: structure parameter
 * @av: vector argument
 *
 * Return: on success 0 , otherwise 1
 */
int hsh(info_t *info, char **av)
{
	ssize_t x = 0;
	int y = 0;

	while (x != -1 && y != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		x = get_input(info);
		if (x != -1)
		{
			set_info(info, av);
			y = find_builtin(info);
			if (y == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (y == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (y);
}

/**
 * find_builtin - finds command of builtin
 * @info: structure parameter
 *
 * Return: executed successfully 0, not found -1, not successful 1, otherwise -2
 */
int find_builtin(info_t *info)
{
	int x, return_val = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (_strcmp(info->argv[0], builtintbl[x].type) == 0)
		{
			info->line_count++;
			return_val = builtintbl[x].func(info);
			break;
		}

	return (return_val);
}

/**
 * find_cmd - finds path command
 * @info: structure parameter
 *
 * Return: no return (void)
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int x, y;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (x = 0, y = 0; info->arg[x]; x++)
		if (!is_delim(info->arg[x], " \t\n"))
			y++;
	if (!y)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks an exec thread
 * @info: structure parameter
 *
 * Return: no return (void)
 */
void fork_cmd(info_t *info)
{
	pid_t x;

	x = fork();
	if (x == -1)
	{
		perror("Error:");
		return;
	}
	if (x == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
            {
				exit(126);
            }
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
            {
				print_error(info, "Permission denied\n");
            }
		}
	}
}
