/*
 * repository.h
 *
 *  Created on: Apr 23, 2020
 *      Author: zamek
 */

#ifndef REPOSITORY_H_
#define REPOSITORY_H_

#include <stdlib.h>
#include <sys/queue.h>

enum type_t {
	CAR, ENGINE, SHIP, TRUCK, UNKNOWN
};

struct unit_t {
	enum type_t type;
	int pieces;
	int unit_price;
	char *name;
	TAILQ_ENTRY(unit_t) next;
};


int rep_open(const char *file);

int rep_close(const char *file);

int rep_enqueue(enum type_t type, const char *name, int pieces, int unit_price);

struct unit_t *rep_find_unit(enum type_t type, const char *name);

struct unit_t *rep_dequeue(enum type_t type, const char *name, int pieces);

int rep_count_type(enum type_t type);

int rep_sum_price();

int rep_free_unit(struct unit_t *u);

int rep_is_empty();

#endif /* REPOSITORY_H_ */
