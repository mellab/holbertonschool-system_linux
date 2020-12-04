#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <grp.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

/**
 * struct option - ls options
 * @reverse: sort in reverse
 * @recursive: list sub-directories recursively
 * @sortingbysize: sort by size
 * @sortingbytime: sort by time
 * @longformat: show long format
 * @pereachline: contents per line
 * @hiddennav: doesn't show directories paths
 * @allhidden: shows all contents, including hidden files
 */

typedef struct option
{
	bool reverse;
	bool recursive;
	bool sortingbysize;
	bool sortingbytime;
	bool longformat;
	bool pereachline;
	bool hiddennav;
	bool allhidden;
};

/* Main */

void choptions(struct option **options, char *argv[], size_t i, size_t j);
void initialoptions(struct option **options);
void clearout(struct content *entries, struct content *dir,
		struct option *opt);
size_t errormsgs(char *arg, char opt, bool outlet, bool printed);


#endif /*HEADER_H*/
