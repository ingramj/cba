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
test_cba_true(void)
{
	return cba_true();
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

	RUN_TEST(test_cba_true);

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
