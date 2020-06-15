/*
 * repository.c
 *
 *  Created on: Apr 23, 2020
 *      Author: zamek
 */

#include <stdlib.h>
#include <syslog.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <repository.h>
#include <macros.h>

#define DEBUG
#define BUFFER_SIZE 256
#define DELIMITER ";"

#define ERR_REPO_NOT_INITIALIZED "repository not initialized"
#define ERR_REPO_ALREADY_INITIALIZED "repository already initialized"
#define ERR_MUTEX_LOCK_FAILED "Mutex lock failed"
#define ERR_MUTEX_UN_LOCK_FAILED "Mutex unlock failed"
#define ERR_TYPE_INVALID "type invalid"
#define ERR_NAME_IS_EMPTY_OR_NULL "name is empty or null"
#define ERR_PIECES_IS_ZERO_OR_NEGATIVE "pieces is zero or negative"
#define ERR_NAME_IS_EMPTY_OR_NULL "name is empty or null"
#define ERR_TYPE_IS_WRONG "type is wrong"
#define ERR_LINE_IS_EMPTY "Line is empty"

static struct {
	int initialized;
	pthread_mutex_t mutex;
	TAILQ_HEAD(p_list, unit_t)
	head;
} repository = {
		.initialized = 0,
		.mutex = PTHREAD_MUTEX_INITIALIZER
};

static char *str_chomp(char *buffer) {
#ifdef DEBUG
	syslog(LOG_DEBUG, "Enter str_chomp, buffer:%s", buffer);
#endif

	if (!buffer || !*buffer)
		return (buffer);

	char *begin = buffer;

	while (*buffer++)
		;

	while (--buffer >= begin) {
		if (*buffer >= ' ')
			return (begin);

		if (*buffer == '\r' || *buffer == '\n')
			*buffer = '\0';
	}
	return begin;
}

static int create_unit(enum type_t type, int pieces, int unit_price,
		const char *name) {
#ifdef DEBUG
	syslog(LOG_DEBUG,
			"Enter create_unit, type:%d, pieces:%d, unit_price:%d, name: %s",
			type, pieces, unit_price, name);
#endif
	if (!(type >= CAR && type <= UNKNOWN && pieces >= 0 && unit_price >= 0
			&& name && *name)) {
		syslog(LOG_WARNING, "create_unit input error");
		return EXIT_FAILURE;
	}

	struct unit_t *result;
	MALLOC(result, sizeof(struct unit_t));

	return EXIT_SUCCESS;
}

static void process_line(char *line) {
#ifdef DEBUG
	syslog(LOG_DEBUG, "Enter process_line, line:%s", line);
#endif
	if (!(line && *line)) {
		syslog(LOG_WARNING, ERR_LINE_IS_EMPTY);
		return;
	}

}

static int load_from_file(const char *file) {
#ifdef DEBUG
	syslog(LOG_DEBUG, "Enter load_from_file, file:%s", file);
#endif
	if (!(file && *file)) {
		syslog(LOG_ERR, "file is null or empty");
		return EXIT_SUCCESS;
	}

	FILE *f = fopen(file, "r");
	if (!f) {
		syslog(LOG_WARNING, "cannot open file, result:%s", strerror(errno));
		return errno == ENOENT ? EXIT_SUCCESS : EXIT_FAILURE;
	}

	char *line;
	MALLOC(line, BUFFER_SIZE);
	while ((line = fgets(line, BUFFER_SIZE, f)))
		process_line(line);

	FREE(line);
	fclose(f);
	return EXIT_SUCCESS;
}

static int save_to_file(const char *file) {
#ifdef DEBUG
	syslog(LOG_DEBUG, "Enter save_to_file, file:%s", file);
#endif

	if (!(file && *file)) {
		syslog(LOG_ERR, "file is null or empty");
		return EXIT_FAILURE;
	}

	FILE *f = fopen(file, "w");
	if (!f) {
		syslog(LOG_WARNING, "cannot open file, result:%s", strerror(errno));
		return EXIT_FAILURE;
	}


	fclose(f);
	return EXIT_SUCCESS;
}

int rep_open(const char *file) {
#ifdef DEBUG
	syslog(LOG_DEBUG, "Enter rep_open, file:%s", file);
#endif

	if (repository.initialized) {
		syslog(LOG_ERR, "repository already initialized");
		return EXIT_FAILURE;
	}

	TAILQ_INIT(&repository.head);

	if (pthread_mutex_init(&repository.mutex, NULL)) {
		syslog(LOG_ERR, "Cannot initialize mutex");
		return EXIT_FAILURE;
	}

	if (file && *file && (load_from_file(file) != EXIT_SUCCESS)) {
		syslog(LOG_WARNING, "File load error %s", file);
		return EXIT_FAILURE;
	}

	repository.initialized = 1;
	return EXIT_SUCCESS;
}

int rep_close(const char *file) {
#ifdef DEBUG
	syslog(LOG_DEBUG, "Enter rep_close file:%s", file);
#endif
	if (!repository.initialized) {
		syslog(LOG_ERR, ERR_REPO_NOT_INITIALIZED);
		return EXIT_FAILURE;
	}

	if (file && *file && (save_to_file(file) != EXIT_SUCCESS)) {
		syslog(LOG_ERR, "Cannot save file:%s", file);
		return EXIT_FAILURE;
	}

	while (!TAILQ_EMPTY(&repository.head)) {
		struct unit_t *u = TAILQ_FIRST(&repository.head);
		TAILQ_REMOVE(&repository.head, u, next);
	}

	if (pthread_mutex_destroy(&repository.mutex)) {
		syslog(LOG_ERR, "Cannot destroy mutex");
		return EXIT_FAILURE;
	}

	repository.initialized = 0;
	return EXIT_SUCCESS;
}

int rep_enqueue(enum type_t type, const char *name, int pieces, int unit_price) {
#ifdef DEBUG
	syslog(LOG_DEBUG, "Enter rep_enqueue, type:%d name:%s, pieces:%d", type, name,
			pieces);
#endif

	return EXIT_SUCCESS;
}

struct unit_t *rep_find_unit(enum type_t type, const char *name) {
#ifdef DEBUG
	syslog(LOG_DEBUG, "Enter rep_find_unit type:%d, name:%s", type, name);
#endif
	if (!repository.initialized) {
		syslog(LOG_ERR, ERR_REPO_NOT_INITIALIZED);
		return NULL;
	}


	return NULL;
}

struct unit_t *rep_dequeue(enum type_t type, const char *name, int pieces) {
#ifdef DEBUG
	syslog(LOG_DEBUG, "Enter rep_output, type:%d, name:%s, pieces:%d", type,
			name, pieces);
#endif

	struct unit_t *u = rep_find_unit(type, name);
	if (u) {
		if (u->pieces >= pieces)
			u->pieces -= pieces;
		else {
			syslog(LOG_INFO, "There is not enough pieces for %s %d", name,
					pieces);
			goto exit;
		}
	}

exit:

	return u;
}

int rep_count_type(enum type_t type) {
#ifdef DEBUG
	syslog(LOG_DEBUG, "Enter rep_count_type, type:%d", type);
#endif
	int sum = 0;

	return sum;
}

int rep_sum_price() {
#ifdef DEBUG
	syslog(LOG_DEBUG, "Enter rep_sum_price");
#endif
	int sum = 0;

	return sum;
}

int rep_free_unit(struct unit_t *u) {
#ifdef DEBUG
	syslog(LOG_DEBUG, "Enter rep_sum_unit, u is null:%s", u ? "false" : "true");
#endif
	if (!u) {
		syslog(LOG_WARNING, "rep_free_unit u is null");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int rep_is_empty() {
#ifdef DEBUG
	syslog(LOG_DEBUG, "Enter rep_is_empty");
#endif

}
