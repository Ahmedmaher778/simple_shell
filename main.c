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
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			if (errno == EACCES)
            {
				exit(126);
            }
			return (EXIT_FAILURE);
		}
		info->readfd = fileDirectory;
	}
	read_history(info);
	hsh(info, av);
	populate_env_list(info);
	return (EXIT_SUCCESS);
}
