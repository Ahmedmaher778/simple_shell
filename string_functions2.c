#include "shell.h"

/**
 * _strcpy - function copies a string
 * @dest: is the destination
 * @src: is the source
 *
 * Return: destination
 */
char *_strcpy(char *dest, char *src)
{
	int x = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[x])
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = 0;
	return (dest);
}

/**
 * _strdup - function duplicates a string
 * @str: is a string
 *
 * Return: string
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *returnValue;

	if (str == NULL)
    {
		return (NULL);
    }
	while (*str++)
		len++;
	returnValue = malloc(sizeof(char) * (len + 1));
	if (!returnValue)
    {
		return (NULL);
    }
	for (len++; len--;)
    {
		returnValue[len] = *--str;
    }
	return (returnValue);
}

/**
 *_puts - function prints an input string
 *@str: is a string
 *
 * Return: no return (void)
 */
void _puts(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}

/**
 * _putchar - function writes c to stdout
 * @c: is the character
 *
 * Return: on success 1, on error -1
 */
int _putchar(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c != BUF_FLUSH)
    {
		buf[x++] = c;
    }
	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buf, x);
		x = 0;
	}
	return (1);
}
