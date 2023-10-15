#include "shell.h"

/**
 *_eputs - prints an input string
 * @str: string to be printed
 * Return: Nothing
*/

void _eputs(char *str)
{
	int l = 0;

	if (!str)
		return;
	while (str[l] != '\0')
	{
		_eputchar(str[l]);
		l++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately
*/

int _eputchar(char c)
{
	static int l;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || l >= WRITE_BUF_SIZE)
	{
		write(2, buf, l);
		l = 0;
	}
	if (c != BUF_FLUSH)
		buf[l++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: character to print
 * @fd: filedescriptor to write to
 * Return: On success 1
 * On error, -1 is returned, and errno is set appropriately
*/

int _putfd(char c, int fd)
{
	static int l;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || l >= WRITE_BUF_SIZE)
	{
		write(fd, buff, l);
		l = 0;
	}
	if (c != BUF_FLUSH)
		buff[l++] = c;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @str: string to be printed
 * @fd: filedescriptor to write to
 * Return: number of chars put
*/

int _putsfd(char *str, int fd)
{
	int l = 0;

	if (!str)
		return (0);
	while (*str)
	{
		l += _putfd(*str++, fd);
	}
	return (l);
}
