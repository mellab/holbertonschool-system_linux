#ifndef _GETLINE_H_
#define _GETLINE_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define READ_SIZE 1

/**
 * struct descriptor_s - singly linked list  of file descriptors
 * @fd: file descriptor
 * @buf: character buffer
 * @pos: current position of the buffer
 * @next: points to the next node
 *
 * Description: singly linked list node structure,
 * which holds a file descirptor
 */

typedef struct descriptor_s
{
	int fd;
	char buf[READ_SIZE];
	size_t pos;
	struct descriptor_s *next;
} descriptor_t;

char *_getline(const int fd);

#endif /* _GETLINE_H_ */
