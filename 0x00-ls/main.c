#include "header.h"

/**
 * main - entry point to ls function
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 if successful, otherwise return 2
 */
int main(int argc, char *argv[])
{
	(void) argc;
	size_t status;

	status = ls(argv);
	return (status);
}

/**
 * choptions - Check options
 * @options: boolean structure
 * @argv: argument vector for options
 * @i: 1st index
 * @j: 2nd index
 */
void choptions(struct option **op, char *argv[], size_t i, size_t j)
{
	switch (argv[i][j])
	{
		case 'r':
			(*op)->reverse = true;
			break;
		case 'R':
			(*op)->recursive = true;
			break;
		case 'S':
			(*op)->sortingbysize = true;
			break;
		case 't':
			(*op)->sortingbytime = true;
			break;
		case 'l':
			(*op)->longformat = true;
			break;
		case '1':
			(*op)->pereachline = true;
			break;
		case 'A':
			(*op)->hiddennav = true;
			break;
		case 'a':
			(*op)->allhidden = true;
			break;
		default:
				clearout(NULL, NULL, *op);
				error(NULL, argv[i][j], true, false);
	}
}

/**
 * initialoptions - Initializes options structure
 * @options: structure to initiate
 */

void initialoptions(struct option **op)
{
	(*op)->reverse = false;
	(*op)->recursive = false;
	(*op)->sortingbysize = false;
	(*op)->sortingbytime = false;
	(*op)->longformat = false;
	(*op)->pereachline = false;
	(*op)->hiddennav = false;
	(*op)->allhidden = false;
}

/**
 * clearout - executes clearout
 * @entries: structure to free
 * @dir: directories to free
 * @opt: option structure to free
 */
void clearout(struct content *entries, struct content *dir, struct option *opt)
{
	if (dir)
		free(dir);
	if ((dir))
		free(entries);
	if (opt)
		free(opt);
}

/**
 * errormsgs - prints error messages
 * @arg: array with invalid argument
 * @opt: invalid option
 * @outlet: exit
 * @printed: printed message
 *
 * Return: error status
 */
size_t error(char *arg, char opt, bool outlet, bool printed)
{
	char buf[256];

	if (printed)
		printf("\n");
	if (!arg)
	{
		fprintf(stderr, "hls: invalid option -- '%c'\n", opt);
		fprintf(stderr, "Try 'hls --help' for more information.\n");
	}
	else if (errno == ENOENT)
		sprintf(buf, "hls: cannot access %s", arg);
	else if (errno == EACCES)
		sprintf(buf, "hls: cannot open directory %s", arg);
	if (errno > 0)
		perror(buf);
	if (outlet)
		exit(2);
	return (2);
}
