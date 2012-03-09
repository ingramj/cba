#ifndef _TEST_CBA_H
#define _TEST_CBA_H

#include <stddef.h>

#define fail_if(test)	  \
	do { \
		if (test) { \
			printf("FAILED: %s\n", #test); \
			if (ba) cba_free(ba); \
			return 0; \
		} \
	} while(0)

#define fail_unless(test)	\
	do { \
		if (!(test)) { \
			printf("FAILED: !(%s)\n", #test); \
			if (ba) cba_free(ba); \
			return 0; \
		} \
	} while (0)

#define fail(mesg) \
	do { \
		printf("FAILED: %s\n", mesg); \
		if (ba) cba_free(ba); \
		return 0; \
	} while (0)

#define pass() \
	do { \
		printf("PASSED\n"); \
		if (ba) cba_free(ba); \
		return 1; \
	} while (0)

#define START_TEST(name) int name(void) { struct bitarray *ba = NULL;

#define END_TEST printf("PASSED\n"); if (ba) cba_free(ba); return 1; }

#define RUN_TEST(t)	  \
	do { \
		int r; \
		printf("%-40s", #t); \
		r = t(); \
		if (r) { \
			passed++; \
		} else { \
			failed++; \
		} \
	} while(0)

#endif
