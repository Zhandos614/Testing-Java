/*
 * test.c
 *
 *  Created on: Apr 23, 2020
 *      Author: zamek
 */

#include <stdlib.h>
#include <stdio.h>
#include <CUnit/Basic.h>
#include <pthread.h>
#include <syslog.h>

#include <macros.h>
#include <repository.h>

#define FILE_NAME "repository.ser"

#define NO_THREAD

#define TEST_COUNTS 10

#define TOYOTA "Toyota Yaris Hybrid"
#define VW "Volkswagen Golf"
#define FP "Fountaine Pajot"

pthread_t enqueuer;
pthread_t dequeuer;

int before_test() {
	remove(FILE_NAME);
	return 0;
}


int after_test() {
	return 0;
}


void open_test() {
	CU_ASSERT_EQUAL(EXIT_FAILURE, rep_close(FILE_NAME));
	CU_ASSERT_EQUAL(0, rep_count_type(CAR));
	CU_ASSERT_PTR_NULL(rep_dequeue(CAR, TOYOTA, 1));
	CU_ASSERT_EQUAL(EXIT_FAILURE, rep_enqueue(SHIP, FP, 1, 450000));
	CU_ASSERT_PTR_NULL(rep_find_unit(SHIP, FP));
	CU_ASSERT_EQUAL(0, rep_sum_price());
	CU_ASSERT_TRUE(rep_is_empty());

	CU_ASSERT_EQUAL(EXIT_SUCCESS, rep_open(FILE_NAME));
	CU_ASSERT_EQUAL(EXIT_FAILURE, rep_open(NULL));
}

void close_test() {
	CU_ASSERT_EQUAL(EXIT_SUCCESS, rep_close(FILE_NAME));

	CU_ASSERT_EQUAL(EXIT_FAILURE, rep_close(FILE_NAME));

	CU_ASSERT_EQUAL(EXIT_FAILURE, rep_close(NULL));

	CU_ASSERT_EQUAL(0, rep_count_type(CAR));
	CU_ASSERT_PTR_NULL(rep_dequeue(CAR, TOYOTA, 1));
	CU_ASSERT_EQUAL(EXIT_FAILURE, rep_enqueue(SHIP, FP, 1, 450000));
	CU_ASSERT_PTR_NULL(rep_find_unit(SHIP, FP));
	CU_ASSERT_EQUAL(0, rep_sum_price());
	CU_ASSERT_TRUE(rep_is_empty());
}

void *enqueue(void *p) {
	char buffer[25];

	CU_ASSERT_TRUE(rep_is_empty());

	CU_ASSERT_EQUAL(EXIT_FAILURE, rep_enqueue(CAR, NULL, 1, 1000));
	CU_ASSERT_EQUAL(EXIT_FAILURE, rep_enqueue(-1, NULL, 1, 1000));
	CU_ASSERT_EQUAL(EXIT_FAILURE, rep_enqueue(UNKNOWN, NULL, 1, 1000));

	int sum=0;
	for (int i=0;i<TEST_COUNTS;++i) {
		sprintf(buffer, "%s%d", TOYOTA, i);
		CU_ASSERT_EQUAL(EXIT_SUCCESS, rep_enqueue(CAR, buffer, i+1, 1000));
		sum += i+1;
	}

	CU_ASSERT_EQUAL(sum, rep_count_type(CAR));

	CU_ASSERT_FALSE(rep_is_empty());
	for (int i=ENGINE;i<UNKNOWN;++i)
		CU_ASSERT_EQUAL(0, rep_count_type(i));

	sprintf(buffer, "%s%d", TOYOTA, 1);
	CU_ASSERT_PTR_NOT_NULL(rep_find_unit(CAR, buffer));
	CU_ASSERT_PTR_NULL(rep_find_unit(UNKNOWN, buffer));
	CU_ASSERT_PTR_NULL(rep_find_unit(CAR, NULL));
	CU_ASSERT_PTR_NULL(rep_find_unit(CAR, ""));

	CU_ASSERT_PTR_NULL(rep_dequeue(UNKNOWN, buffer, 0));
	CU_ASSERT_PTR_NULL(rep_dequeue(UNKNOWN, NULL, 0));

	return NULL;
}

void *dequeue(void *p) {
	char buffer[25];

	CU_ASSERT_FALSE(rep_is_empty());
	for (int i=0;i<TEST_COUNTS;++i) {
		sprintf(buffer, "%s%d", TOYOTA, i);
		struct unit_t *u=rep_dequeue(CAR, buffer, i+1);
		CU_ASSERT_PTR_NOT_NULL(u);
		CU_ASSERT_EQUAL(u->unit_price, 1000);
		CU_ASSERT_STRING_EQUAL(buffer, u->name);
	}
	return NULL;
}

void test() {

#ifdef NO_THREAD
	syslog(LOG_WARNING, "NO THREAD TEST");
	enqueue(NULL);
	dequeue(NULL);
#else
	syslog(LOG_WARNING, "THREAD TEST");
	pthread_create(&enqueuer, NULL, enqueue, NULL);
	pthread_create(&dequeuer, NULL, dequeue, NULL);
	pthread_join(enqueuer, NULL);
	pthread_join(dequeuer, NULL);
#endif

}

void reopen_test() {
	remove(FILE_NAME);
	CU_ASSERT_EQUAL(EXIT_SUCCESS, rep_open(FILE_NAME));
	CU_ASSERT_TRUE(rep_is_empty());

	enqueue(NULL);

	CU_ASSERT_EQUAL(EXIT_SUCCESS, rep_close(FILE_NAME));

	CU_ASSERT_EQUAL(EXIT_SUCCESS, rep_open(FILE_NAME));
	CU_ASSERT_FALSE(rep_is_empty());
	dequeue(NULL);
	CU_ASSERT_EQUAL(EXIT_SUCCESS, rep_close(FILE_NAME));
}

int main() {

	openlog("REPOSITRY TEST", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
	setlogmask (LOG_UPTO (LOG_DEBUG));

	CU_pSuite suite =NULL;
	if (CUE_SUCCESS!=CU_initialize_registry())
		goto exit;

	suite = CU_add_suite("Suite 1", before_test, after_test);
	if (NULL==suite) {
		CU_cleanup_registry();
		goto exit;
	}

	if ( (NULL==CU_add_test(suite, "Open test", open_test)) ||
		 (NULL==CU_add_test(suite, "test", test)) ||
		 (NULL==CU_add_test(suite, "Close test", close_test)) ||
		 (NULL==CU_add_test(suite, "Reopen test", reopen_test)) ) {
		CU_cleanup_registry();
		goto exit;
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

exit:
	closelog();
	return CU_get_error();
}
