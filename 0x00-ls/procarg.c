#include "header.h"

void parsesym(char *arg, size_t *fc, size_t *dc, size_t *file_a, size_t *dir_a,
		size_t i, size_t len)
{
	char *buf, *path;
	ssize_t bufsiz, nbytes;
	struct stat sb;

	bufsiz = len;
	if (len == 0)
		bufsiz = PATH_MAX;
	buf = malloc(bufsiz);
	if (!buf)
		exit(2);
	path = malloc(bufsiz + 2);
	if (!path)
		exit(2);
	nbytes = readlink(arg, buf, bufsiz);
	if (nbytes == -1)
		exit(2);
	_memcpy(path, "/", 1);
	_memcpy(path + 1, buf, bufsiz);
	path[1 + bufsiz] = '\0';
	lstat(path, &sb);
	free(buf);
	free(path);
	if ((sb.st_mode & S_IFMT) == S_IFREG)
		file_a[(*fc)++] = i;
	else if ((sb.st_mode & S_IFMT) == S_IFDIR)
		dir_a[(*dc)++] = i;
}

/**
 * printfile - prints and formats files
 * @entries: pointer content entries to print
 * @opt: options state
 * @c: count of entries
 */
void printfile(struct content *entries, struct option *opt, size_t c)
{
	size_t i;
	static bool start;

	for (i = 0; i < c; ++i)
	{
		if (start)
			!opt->pereachline ? printf("  ") : printf("\n");
		printf("%s", entries[i].name);
		start = true;
	}
	printf("\n");
}

/**
 * handlecontent - creates entries and prints if file
 * @f: if file
 * @argv: pointer to array of arguments
 * @a: pointer to array of file or directory indexes
 * @c: content count
 * @printed: if files have been printed
 * @opt: options state
 *
 * Return: created entries or NULL if file
 */
content *handlecontent(bool f, char *argv[], size_t *a, size_t c,
		bool *printed, struct option *opt)
{
	size_t i;
	struct content *entries;

	entries = malloc(c * sizeof(*entries));
	if (!entries)
		exit(2);
	for (i = 0; i < c; ++i)
	{
		_strcpy(entries[i].name, argv[a[i]]);
		if (opt->longformat && f)
			linfo(NULL, &entries[i]);
	}
	if (f)
	{
		if (opt->longformat)
			plong(entries, c, true, opt, NULL);
		else
			printfile(entries, opt, c);
		*printed = true;
		clearout(entries, NULL, NULL);
	}
	return (entries);
}

/**
 * processargs - process arguments
 * @dirs: pointer to pointer of directories
 * @opt: pointer to options struct
 * @argv: pointer to array of arguments
 * @file_a: pointer to array containing file indexes
 * @dir_a: pointer to array containing directory indexes
 * @status: current error status
 * @dp: pointer to directory pointer
 * @fc: file count
 * @dc: directory count
 * @erc: error count
 * @printed: if files have been printed
 *
 * Return: error status
 */
size_t processargs(struct content **dirs, struct option *opt, char *argv[],
		size_t *file_a, size_t *dir_a, size_t status, DIR **dp,
		size_t fc, size_t dc, size_t erc, bool *printed)
{
	*dirs = NULL;
	if (dc == 0 && fc == 0 && erc == 0)
	{
		*dp = opendir(".");
		if (!*dp)
		{
			clearout(NULL, NULL, opt);
			error(".", '\0', true, *printed);
		}
	}
	else
	{
		if (fc > 0)
			handlecontent(true, argv, file_a, fc, printed, opt);
		if (dc > 0)
		{
			*dirs = handlecontent(false, argv, dir_a, dc, printed,
					opt);
			if (!opt->reverse)
				_qsort(*dirs, 0, dc - 1, cmpstringp);
			else
				_qsort(*dirs, 0, dc - 1, revstringp);
		}
	}
	return (status);
}
