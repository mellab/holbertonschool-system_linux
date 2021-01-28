#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * main - Program that displays the information contained in the ELF file
 * header of an ELF file
 * @argc: How many arguments from OS command line
 * @argv: The arguments from OS command line
 * @env: The environment from shell
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char **argv, char **env)
{
	char *av[] = {"/usr/bin/readelf", "-W", "-l", "", NULL};

	(void)argc;
	av[3] = argv[1];
	if (execve("/usr/bin/readelf", av, env) == -1)
	{
		perror("execv");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
