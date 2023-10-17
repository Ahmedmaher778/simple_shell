#include "shell.h"

/**
 * get_history_file - history file
 * @info: structure parameter
 *
 * Return: string
 */

char *get_history_file(info_t *info)
{
	char *buffer, *directory;

	directory = _getenv(info, "HOME=");
	if (!directory)
    {
		return (NULL);
    }
	buffer = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!buffer)
    {
		return (NULL);
    }
	buffer[0] = 0;
	_strcpy(buffer, directory);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - create or append a file
 * @info: structure parameter
 *
 * Return: on success 1, otherwise -1
 */
int write_history(info_t *info)
{
	ssize_t fileDirectory;
	char *name = get_history_file(info);
	list_t *node = NULL;

	if (!name)
    {
		return (-1);
    }

	fileDirectory = open(name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(name);
	if (fileDirectory == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fileDirectory);
		_putfd('\n', fileDirectory);
	}
	_putfd(BUF_FLUSH, fileDirectory);
	close(fileDirectory);
	return (1);
}

/**
 * read_history - reads history
 * @info: structure parameter
 *
 * Return: on success histcount, otherwise 0
 */
int read_history(info_t *info)
{
	int i, latest = 0, counter = 0;
	ssize_t fileDirectory, readedLength, fileSize = 0;
	struct stat st;
	char *buffer = NULL, *name = get_history_file(info);

	if (!name)
		return (0);

	fileDirectory = open(name, O_RDONLY);
	free(name);
	if (fileDirectory == -1)
		return (0);
	if (!fstat(fileDirectory, &st))
		fileSize = st.st_size;
	if (fileSize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fileSize + 1));
	if (!buffer)
		return (0);
	readedLength = read(fileDirectory, buffer, fileSize);
	buffer[fileSize] = 0;
	if (readedLength <= 0)
		return (free(buffer), 0);
	close(fileDirectory);
	for (i = 0; i < fileSize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_history_list(info, buffer + latest, counter++);
			latest = i + 1;
		}
	if (latest != i)
		build_history_list(info, buffer + latest, counter++);
	free(buffer);
	info->histcount = counter;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to list
 * @info: structure parameter
 * @buf: buffer
 * @linecount: linecount history
 *
 * Return: 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
    {
		node = info->history;
    }

	add_node_end(&node, buf, linecount);

	if (!info->history)
    {
		info->history = node;
    }

	return (0);
}

/**
 * renumber_history - renumbers the history
 * @info: structure parameter
 *
 * Return: histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int x = 0;

	while (node)
	{
		node->num = x++;
		node = node->next;
	}
	return (info->histcount = x);
}
