#include "header.h"

/**
 * revstringp - reverses regardless of case
 * @p1: 1st string
 * @p2: 2nd string
 *
 * Return: + or -
 */
int revstringp(const void *p1, const void *p2)
{
	char tp1[256];
	char tp2[256];

	str_toupper(_strcpy(tp1, p1));
	str_toupper(_strcpy(tp2, p2));
	return (_strcmp(tp2, tp1));
}

/**
 * cmpstringp - makes a copy of the string to the buffer
 * @p1: 1st string
 * @p2: 2nd string
 *
 * Return: + or -
 */
int cmpstringp(const void *p1, const void *p2)
{
	char tp1[256];
	char tp2[256];

	str_toupper(_strcpy(tp1, p1));
	str_toupper(_strcpy(tp2, p2));
	return (_strcmp(tp1, tp2));
}

/**
 * swap - swaps given data
 * @ent1: first data to swap
 * @ent2: second data to swap
 */
void swap(struct content *ent1, struct content *ent2)
{
	struct content tmp;

	tmp = *ent2;
	*ent2 = *ent1;
	*ent1 = tmp;
}

/**
 * partition - partitions given data into pieces for sorting
 * @entries: data to sort
 * @lo: low
 * @hi: up
 * @cmp: function pointer
 *
 * Return: partition position
 */
size_t partition(struct content *entries, ssize_t lo, ssize_t hi,
		int (*cmp)(const void *p1, const void *p2))
{
	char *piv;
	int i, j;

	piv = entries[hi].name;
	i = lo;
	for (j = lo; j < hi; ++j)
		if (cmp(entries[j].name, piv) <= 0)
		{
			swap(&entries[i], &entries[j]);
			++i;
		}
	swap(&entries[i], &entries[j]);
	return (i);
}

/**
 * _qsort - sorts the data
 * @entries: data to be sorted
 * @lo: low
 * @hi: up
 * @cmp: function reference
 */
void _qsort(struct content *entries, ssize_t lo, ssize_t hi,
		int (*cmp)(const void *p1, const void *p2))
{
	size_t p;

	if (lo < hi)
	{
		p = partition(entries, lo, hi, cmp);
		_qsort(entries, lo, p - 1, cmp);
		_qsort(entries, p + 1, hi, cmp);
	}
}
