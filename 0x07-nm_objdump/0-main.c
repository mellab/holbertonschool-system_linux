#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * main - Reproduces the GNUM nm command
 * @argc: Argument count passed from OS command line
 * @argv: Arguments passed from OS command line
 * @env: Env from shell
 *
 * Return: EXIT_SUCCESS if successful, otherwise return EXIT_FAILURE
 */

int main(int argc, char **argv, char **env)
{
	char *av[] = {"./hnm", "-p", "", NULL};

	(void)argc;
	av[2] = argv[1];
	if (execve("/usr/bin/nm", av, env) == -1)
	{
		perror("execv");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
