#include "shell.h"

/**
 * main - the entry point
 * @ac: count
 * @av: vector
 *
 * Return: on success 0, otherwise 1
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fileDirectory = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fileDirectory)
		: "r" (fileDirectory));

	if (ac == 2)
	{
		fileDirectory = open(av[1], O_RDONLY);
		if (fileDirectory == -1)
		{
			if (errno == EACCES)
			{
				exit(126);
			}
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fileDirectory;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
