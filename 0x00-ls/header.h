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
} option;

/**
 * struct content - stores entry information
 * @name: string buffer
 * @tperm: permissions buffer
 * @lc: link count
 * @uid: user id
 * @gid: group id
 * @usr: user name
 * @grp: group name
 * @siz: content size in bytes
 * @mtim: last modified time
 */
typedef struct content
{
	char name[256];
	char tperm[11];
	long lc;
	long uid;
	long gid;
	char *usr;
	char *grp;
	long siz;
	char mtim[12];
} content;

/* Hls */

size_t ls(char *argv[]);

/* Main */

void choptions(struct option **options, char *argv[], size_t i, size_t j);
void initialoptions(struct option **options);
void clearout(struct content *entries, struct content *dir,
		struct option *opt);
size_t error(char *arg, char opt, bool outlet, bool printed);

/* Strings */
char *_strcpy(char *dest, const char *src);
char *str_toupper(char *s);
int _strcmp(char *s1, char *s2);
size_t _strlen(const char *s);
char *_memcpy(char *dest, char *src, size_t n);

/* Sort */
void _qsort(struct content *entries, ssize_t lo, ssize_t hi,
			int (*cmp)(const void *p1, const void *p2));
int cmpstringp(const void *p1, const void *p2);
int revstringp(const void *p1, const void *p2);

/* Processargs */
size_t processargs(struct content **dirs, struct option *opt, char *argv[],
				   size_t *file_a, size_t *dir_a, size_t status, DIR **dp,
				   size_t fc, size_t dc, size_t erc, bool *printed);
void parsesym(char *arg, size_t *fc, size_t *dc, size_t *file_a, size_t *dir_a,
			  size_t i, size_t len);

/* Options */
bool filterhidden(struct dirent *ep, struct option *opt);
void linfo(char *dirstr, struct content *entries);

/* Options2 */
void setug(struct content *entries, struct stat sb);
void plong(struct content *entries, size_t c, bool f, struct option *opt,
		   char *dirstr);
char *createpath(char *dirstr, char *entry);

#endif /*HEADER_H*/
