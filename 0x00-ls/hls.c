#include "header.h"

static struct option *op;
static bool printed;
static size_t status;

/**
 * printoutput - prints output
 * @entries: entries to print
 * @counter: entries counter
 * @filecounter: file counter
 * @dircount: directory counter
 * @errorcount: error counter
 * @dir: directory to be printed
 * @printed: in case the the printfile was called
 *
 * Return: true after being printed
 */
bool printoutput(struct content *entries, size_t counter, size_t filecounter,
		size_t dircount, size_t errorcount, char *dir, bool printed)
{
	static bool start;
	size_t i;

	if (!op->reverse)
		_qsort(entries, 0, counter - 1, cmpstringp);
	else
		_qsort(entries, 0, counter - 1, revstringp);
	if (filecounter + dircount + errorcount > 1)
	{
		if (start || printed)
			printf("\n");
		printf("%s:\n", dir);
	}
	start = false;
	for (i = 0; i < counter; ++i)
	{
		if (start)
			!op->pereachline ? printf("  ") : printf("\n");
		printf("%s", entries[i].name);
		start = true;
	}
	printf("\n");
	return (true);
}

/**
 * readcontent - reads contents
 * @dp: reference to a directory stream
 * @dirs: reference to directories
 * @entries: reference to a reference of content entries
 * @entrycount: reference to entry count
 * @dircount: directory counter
 * @entsize: size of entries
 * @i: index
 *
 * Return: true if successful, otherwise return false
 */
bool readcontent(DIR *dp, struct content **entries, struct content *dirs,
	size_t *entrycount, size_t dircount, size_t i, size_t *entsize)
{
	struct dirent *ep;

	if (dircount > 0)
	{
		dp = opendir(dirs[i].name);
		if (!dp)
		{
		status = error(dirs[i].name, '\0', false, printed);
			printed = false;
		return (false);
		}
	}
	while ((ep = readdir(dp)))
	{
		if (filterhidden(ep, op))
			continue;
		_strcpy((*entries)[*entrycount].name, ep->d_name);
		if (op->longformat)
			linfo(dirs[i].name, &(*entries)[*entrycount]);
		++*entrycount;
		if (*entrycount == *entsize)
		{
			*entsize *= 2;
			*entries = realloc(*entries, *entsize * sizeof(**entries));
		}
	}
	closedir(dp);
	return (true);
}

/**
 * parse_args - indexes positions of valid arguments, files, and directories
 * @argv: pointer to an array of strings to parse
 * @fc: number of files
 * @dc: number of directories
 * @erc: number of errors
 * @file_a: pointer to array to populate with file indexes
 * @dir_a: pointer to array to populate with directory indexes
 */
void parse_args(char *argv[], size_t *fc, size_t *dc, size_t *erc,
				size_t *file_a, size_t *dir_a)
{
	size_t i, j;
	struct stat sb;

	for (i = 1; argv[i]; ++i)
		if (*argv[i] == '-')
			for (j = 1; argv[i][j]; ++j)
                choptions(&op, argv, i, j);
	for (i = 1; argv[i]; ++i)
		if (lstat(argv[i], &sb) == 0)
		{
			if ((sb.st_mode & S_IFMT) == S_IFLNK)
			{
				if (!op->longformat)
					parsesym(argv[i], fc, dc, file_a,
							 dir_a, i, sb.st_size);
				else
					file_a[(*fc)++] = i;
			}
			else if ((sb.st_mode & S_IFMT) == S_IFREG)
			{
				file_a[(*fc)++] = i;
			}
			else if ((sb.st_mode & S_IFMT) == S_IFDIR)
			{
				dir_a[(*dc)++] = i;
			}
		}
	for (i = 1; argv[i]; ++i)
		if (lstat(argv[i], &sb) == -1 && (*argv[i] != '-' ||
										  _strcmp(argv[i], "-") == 0))
		{
			status = error(argv[i], '\0', false, printed);
			++*erc;
		}
}

/**
 * ls - Lists information about files and directories
 * @argv: pointer to an array of strings containing arguments
 *
 * Return: status
 */
size_t ls(char *argv[])
{
	size_t fc, dc, ec, erc, entsiz, i;
	size_t file_a[256], dir_a[256];
	DIR *dp;
	struct content *entries, *dirs;

	fc = dc = ec = erc = 0;
	entsiz = 100;
	op = malloc(sizeof(*op));
	if (!op)
		exit(2);
	initialoptions(&op);

	parse_args(argv, &fc, &dc, &erc, file_a, dir_a);
	status = processargs(&dirs, op, argv, file_a, dir_a, status, &dp, fc, dc,
						 erc, &printed);
	entries = malloc(entsiz * sizeof(*entries));
	if (!entries)
		exit(2);
	for (i = 0; i < dc || (fc == 0 && dc == 0 && erc == 0); ++i)
	{
		if (!readcontent(dp, &entries, dirs, &ec, dc, i, &entsiz))
			continue;
		if (op->longformat)
			plong(entries, ec, false, op,
				  fc == 0 && dc == 0 ? "." : dirs[i].name);
		else
			printed = printoutput(entries, ec, fc, dc, erc,
								   dirs[i].name, printed);
		if (fc == 0 && dc == 0)
			break;
		ec = 0;
	}
	clearout(entries, dirs, op);
	return (status);
}