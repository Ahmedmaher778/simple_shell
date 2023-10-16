#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 * Return: 1 if interactive mode, 0 otherwise
*/

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: char to check
 * @delim: delimeter string
 * Return: 1 if true, 0 if false
*/

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@c: character to input.
 *Return: 1 if c is alphabetic, 0 otherwise
*/

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@s: string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
*/

int _atoi(char *s)
{
	int l, sgn = 1, flagg = 0, output;
	unsigned int resut = 0;

	for (l = 0;  s[l] != '\0' && flagg != 2; l++)
	{
		if (s[l] == '-')
			sgn *= -1;

		if (s[l] >= '0' && s[l] <= '9')
		{
			flagg = 1;
			resut *= 10;
			resut += (s[l] - '0');
		}
		else if (flagg == 1)
			flagg = 2;
	}

	if (sgn == -1)
		output = -resut;
	else
		output = resut;

	return (output);
}
