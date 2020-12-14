#ifndef LAPS_H
#define LAPS_H

#include<stdio.h>
#include<stdlib.h>

/**
 * struct car - race car date
 * @id: race car unique identifier
 * @laps: laps completed by the car
 * @next: next node
 */
typedef struct car
{
	int id;
	size_t laps;
	struct car *next;
} Car;

void race_state(int *id, size_t size);
#endif /* LAPS_H */
