/* A cheesy testing program for libcba.
 *
 * Each test is a function with no arguments, which returns true if
 * the test passes, and false if it fails. Each test should be added
 * to main() using the RUN_TEST() macro, which prints a message for
 * each test, and increments pass/fail counters.
 */

#include "cba.h"
#include <stdio.h>

int
test_cba_alloc(void)
{
	struct bitarray *ba;
	int r;

	ba = cba_alloc(100);
	if (ba && cba_size(ba) == 100) {
		r = 1;
	} else {
		r = 0;
	}
	cba_free(ba);
	return r;
}

int test_allocate_zero(void)
{
	struct bitarray *ba;
	int r;

	ba = cba_alloc(0);
	if (ba && cba_size(ba) == 0) {
		r = 1;
	} else {
		r = 0;
	}
	cba_free(ba);
	return r;
}

int
test_allocated_clear(void)
{
	struct bitarray *ba;
	int i, r;

	r = 1;
	ba = cba_alloc(100);
	for (i = 0; i < 100; i++) {
		if (cba_getbit(ba, i)) {
			r = 0;
			break;
		}
	}
	cba_free(ba);
	return r;
}

int
test_negative_indices(void)
{
	struct bitarray *ba;
	int i, r;

	r = 1;
	ba = cba_alloc(100);
	for (i = -100; i < 0; i++) {
		if (cba_getbit(ba, i) != 0) {
			r = 0;
			break;
		}
	}
	cba_free(ba);
	return r;
}

int
test_out_of_bounds(void)
{
	struct bitarray *ba;
	int r;

	r = 1;
	ba = cba_alloc(10);
	if (cba_getbit(ba, 10) >= 0) {
		r = 0;
	}
	if (cba_getbit(ba, 50) >= 0) {
		r = 0;
	}
	if (cba_getbit(ba, -11) >= 0) {
		r = 0;
	}
	cba_free(ba);
	return r;
}


void fail(const char *s);
void pass(const char *s);

#define RUN_TEST(t)	  \
	do { \
		int r = t(); \
		if (r) { \
			pass(#t"()"); \
			passed++; \
		} else { \
			fail(#t"()"); \
			failed++; \
		} \
	} while(0)

int
main(void)
{
	int passed, failed;
	passed = failed = 0;

	RUN_TEST(test_cba_alloc);
	RUN_TEST(test_allocate_zero);
	RUN_TEST(test_allocated_clear);
	RUN_TEST(test_negative_indices);
	RUN_TEST(test_out_of_bounds);

	printf("%d tests, %d passed, %d failed\n", failed + passed, passed, failed);

	return (failed ? 1 : 0);
}

void
fail(const char *s)
{
	printf("FAIL: %s\n", s);
}

void
pass(const char *s)
{
	printf("PASS: %s\n", s);
}
