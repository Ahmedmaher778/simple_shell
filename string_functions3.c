#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: destination string to be copied to
 *@src: source string
 *@n: amount of characters to be copied
 *Return: concatenated string
*/

char *_strncpy(char *dest, char *src, int n)
{
	int l, k;
	char *d = dest;

	l = 0;
	while (src[l] != '\0' && l < n - 1)
	{
		dest[l] = src[l];
		i++;
	}
	if (l < n)
	{
		k = l;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (d);
}

/**
 **_strncat - concatenates two strings
 *@dest: first string
 *@src: second string
 *@n: amount of bytes to be maximally used
 *Return: concatenated string
*/

char *_strncat(char *dest, char *src, int n)
{
	int l, k;
	char *d = dest;

	l = 0;
	k = 0;
	while (dest[l] != '\0')
		l++;
	while (src[k] != '\0' && k < n)
	{
		dest[l] = src[k];
		l++;
		k++;
	}
	if (k < n)
		dest[l] = '\0';
	return (d);
}

/**
 **_strchr - locates a character in a string
 *@s: string to be parsed
 *@c: character to look for
 *Return: (s) a pointer to the memory area s
*/

char *_strchr(char *s, char c)
{
		do {
		if (*s == c)
		return (s);
	} while (*s++ != '\0');

	return (NULL);
}

