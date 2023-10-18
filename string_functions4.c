#include "shell.h"

/**
 * **strtow - function splits string to words
 * @str: is the string of input
 * @d: is the delimeter string
 * Return: on success array of strings, otherwise NULL
 */

char **strtow(char *str, char *d)
{
	int x, y, z, v, wordsNum = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (!is_delim(str[x], d) && (is_delim(str[x + 1], d) || !str[x + 1]))
			wordsNum++;

	if (wordsNum == 0)
		return (NULL);
	s = malloc((1 + wordsNum) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, y = 0; y < wordsNum; y++)
	{
		while (is_delim(str[x], d))
			x++;
		z = 0;
		while (!is_delim(str[x + z], d) && str[x + z])
			z++;
		s[y] = malloc((z + 1) * sizeof(char));
		if (!s[y])
		{
			for (z = 0; z < y; z++)
				free(s[z]);
			free(s);
			return (NULL);
		}
		for (v = 0; v < z; v++)
			s[y][v] = str[x++];
		s[y][v] = 0;
	}
	s[y] = NULL;
	return (s);
}

/**
 * **strtow2 - function splits a string to words
 * @str: is the string of input
 * @d: is the delimeter string
 * Return: on success array of strings, otherwise NULL
 */
char **strtow2(char *str, char d)
{
	int x, y, z, v, wordsNum = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != d && str[x + 1] == d) ||
		    (str[x] != d && !str[x + 1]) || str[x + 1] == d)
			wordsNum++;
	if (wordsNum == 0)
		return (NULL);
	s = malloc((1 + wordsNum) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, y = 0; y < wordsNum; y++)
	{
		while (str[x] == d && str[x] != d)
			x++;
		z = 0;
		while (str[x + z] != d && str[x + z] && str[x + z] != d)
			z++;
		s[y] = malloc((z + 1) * sizeof(char));
		if (!s[y])
		{
			for (z = 0; z < y; z++)
				free(s[z]);
			free(s);
			return (NULL);
		}
		for (v = 0; v < z; v++)
			s[y][v] = str[x++];
		s[y][v] = 0;
	}
	s[y] = NULL;
	return (s);
}
