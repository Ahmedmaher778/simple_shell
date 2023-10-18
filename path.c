#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: info struct
 * @path: path to file
 * Return: 1 if true, 0 otherwise
*/

int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: PATH string.
 * @start: starting index.
 * @stop: stopping index.
 * Return: pointer to new buffer.
*/

char *dup_chars(char *pathstr, int start, int stop)
{
	int l = 0, j = 0;
	static char buf[1024];

	for (j = 0, l = start; l < stop; l++)
		if (pathstr[l] != ':')
			buf[j++] = pathstr[l];
	buf[j] = 0;
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: info struct
 * @pathstr: PATH string
 * @cmd: cmd to find
 * Return: full path of cmd if found or NULL.
*/

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	char *path;
	int l = 0, cur_pos = 0;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[l] || pathstr[l] == ':')
		{
			path = dup_chars(pathstr, cur_pos, l);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[l])
				break;
			cur_pos = l;
		}
		l++;
	}
	return (NULL);
}

