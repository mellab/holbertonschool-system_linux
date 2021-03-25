#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * main - Reproduces the GNU objdump command
 * @argc: Argument count passed from OS command line
 * @argv: Arguments passed from OS command line
 * @env: Environment from shell
 *
 * Return: EXIT_SUCCESS if successful, otherwise return EXIT_FAILURE
 */

int main(int argc, char **argv, char **env)
{
	char *av[] = {"./hobjdump", "-sf", "", NULL};

	(void)argc;
	av[2] = argv[1];
	if (execve("/usr/bin/objdump", av, env) == -1)
	{
		perror("execv");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
