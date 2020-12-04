include "header.h"

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
void choptions(struct option **options, char *argv[], size_t i, size_t j)
{
	switch (argv[i][j])
	{
		case 'r':
			(*options)->reverse = true;
			break;
		case 'R':
			(*options)->recursive = true;
			break;
		case 'S':
			(*options)->sortingbysize = true;
			break;
		case 't':
			(*options)->sortingbytime = true;
			break;
		case 'l':
			(*options)->longformat = true;
			break;
		case '1':
			(*options)->pereachline = true;
			break;
		case 'A':
			(*options)->hiddennav = true;
			break;
		case 'a':
			(*options)->allhidden = true;
			break;
		default:
				cleanup(NULL, NULL, *options);
				error(NULL, argv[i][j], true, false);
	}
}

/**
 * initialoptions - Initializes options structure
 * @options: structure to initiate
 */

void initialoptions(struct option **options)
{
	(*options)->reverse = false;
	(*options)->recursive = false;
	(*options)->sortingbysize = false;
	(*options)->sortingbytime = false;
	(*options)->longformat = false;
	(*options)->pereachline = false;
	(*options)->hiddennav = false;
	(*options)->allhidden = false;
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
size_t errormsgs(char *arg, char opt, bool outlet, bool printed)
{
	char buf[256];

	if (printed)
		printf("\n");
	if (!arg)
	{
		frpintf(stderr, "hls: invalid option -- '%c'\n", opt);
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
