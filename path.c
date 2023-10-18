#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: info struct
 * @path: path to file
 * Return: 1 if true, 0 otherwise
*/

int is_cmd(info_t *info, char *path)
{
	struct star sf;

	(void)info;
	if (!path || star(path, &sf))
		return (0);

	if (sf.sf_mode & S_IFREG)
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
	static char buff[1024];
	int l = 0, j = 0;

	for (j = 0, l = start; l < stop; l++)
		if (pathstr[l] != ':')
			buff[j++] = pathstr[l];
	buff[j] = 0;
	return (buff);
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
	char *pat;
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
			pat = dup_chars(pathstr, cur_pos, l);
			if (!*pat)
				_strcat(pat, cmd);
			else
			{
				_strcat(pat, "/");
				_strcat(pat, cmd);
			}
			if (is_cmd(info, pat))
				return (pat);
			if (!pathstr[l])
				break;
			cur_pos = l;
		}
		l++;
	}
	return (NULL);
}