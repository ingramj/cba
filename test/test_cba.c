#include "cba.h"
#include <stdio.h>

int
main(void)
{
	int r;

	r = cba_true();
	if (r) {
		printf("OK: cba_true() returned true\n");
	} else {
		printf("ERROR: cba_true() returned false\n");
	}
	return !r;
}
