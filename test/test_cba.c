/* A cheesy testing program for libcba.
 *
 * Tests are defined using the START_TEST(name) macro, and must end with
 * END_TEST. They are run by adding a RUN_TEST(name) call to main(), at the
 * bottom of this file.
 *
 * An uninitialized bitarray struct named ba is available inside each test. It
 * must be initialized before use, but it will be automatically freed when the
 * test ends.
 *
 * The fail_if() and fail_unless() macros can be used to test boolean
 * expressions. fail_if() will cause the test to fail if the the expression is
 * true, and fail_unless() will fail if the expression is false.
 *
 * IMPORTANT: There should be no return statements inside of the test. To
 * return early, use the pass() and fail(mesg) macros; otherwise a memory leak
 * may occur.
 */

#include "cba.h"
#include "test_cba.h"
#include <stdio.h>

START_TEST(test_cba_alloc) {
	ba = cba_alloc(100);
	fail_unless(ba && cba_size(ba) == 100);
} END_TEST


START_TEST(test_allocate_zero) {
	ba = cba_alloc(0);
	fail_unless(ba && cba_size(ba) == 0);
} END_TEST


START_TEST(test_allocated_clear) {
	int i;

	ba = cba_alloc(100);
	for (i = 0; i < 100; i++) {
		fail_if(cba_get(ba, i));
	}
} END_TEST


START_TEST(test_negative_indices) {
	int i;

	ba = cba_alloc(100);
	for (i = -100; i < 0; i++) {
		fail_if(cba_get(ba, i) != 0);
	}
} END_TEST


START_TEST(test_out_of_bounds) {
	ba = cba_alloc(10);
	fail_if(cba_get(ba, 10) >= 0);
	fail_if(cba_get(ba, 50) >= 0);
	fail_if(cba_get(ba, -11) >= 0);
} END_TEST


START_TEST(test_cba_set) {
	int i;

	ba = cba_alloc(100);
	for (i = 0; i < 100; i++) {
		fail_if(cba_get(ba, i) != 0);
		fail_if(cba_set(ba, i) < 0);
		fail_if(cba_get(ba, i) != 1);
	}
} END_TEST


START_TEST(test_cba_clear) {
	int i;

	ba = cba_alloc(100);
	for (i = 0; i < 100; i++) {
		fail_if(cba_clear(ba, i) < 0);
		fail_if(cba_get(ba, i) != 0);
	}
} END_TEST


START_TEST(test_set_then_clear) {
	int i;

	ba = cba_alloc(100);
	for (i = 0; i < 100; i++) {
		fail_if(cba_set(ba, i) < 0);
		fail_if(cba_get(ba, i) != 1);
		fail_if(cba_clear(ba, i) < 0);
		fail_if(cba_get(ba, i) != 0);
	}
} END_TEST


START_TEST(test_cba_set_all) {
	int i;

	ba = cba_alloc(100);
	cba_set_all(ba);
	for (i = 0; i < 100; i++) {
		fail_if(cba_get(ba, i) != 1);
	}
} END_TEST


START_TEST(test_set_all_empty) {
	ba = cba_alloc(0);
	cba_set_all(ba);
} END_TEST


START_TEST(test_cba_clear_all) {
	int i;

	ba = cba_alloc(100);
	cba_clear_all(ba); /* should do nothing. */
	for (i = 0; i < 100; i++) {
		fail_if(cba_get(ba, i) != 0);
	}
} END_TEST


START_TEST(test_clear_all_empty) {
	ba = cba_alloc(0);
	cba_clear_all(ba);
} END_TEST


START_TEST(test_set_all_then_clear_all) {
	int i;

	ba = cba_alloc(100);
	cba_set_all(ba);
	for (i = 0; i < 100; i++) {
		fail_if(cba_get(ba, i) != 1);
	}
	cba_clear_all(ba);
	for (i = 0; i < 100; i++) {
		fail_if(cba_get(ba, i) != 0);
	}
} END_TEST


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
	RUN_TEST(test_cba_set);
	RUN_TEST(test_cba_clear);
	RUN_TEST(test_set_then_clear);
	RUN_TEST(test_cba_set_all);
	RUN_TEST(test_set_all_empty);
	RUN_TEST(test_cba_clear_all);
	RUN_TEST(test_clear_all_empty);
	RUN_TEST(test_set_all_then_clear_all);

	printf("%d tests, %d passed, %d failed\n", failed + passed, passed, failed);

	return (failed ? 1 : 0);
}
