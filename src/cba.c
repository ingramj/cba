#include "cba.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct bitarray {
	long bits;
	long array_sz;
	unsigned int *array;
};


/* Check bounds and convert negative indices.
 * Returns converted index, or -1 on out-of-bounds.
 */
static long
index(struct bitarray *ba, long i)
{
	assert(ba);
	if (i < 0) i += ba->bits;
	return (i >= ba->bits) ? -1 : i;
}


struct bitarray *
cba_alloc(long bits)
{
	struct bitarray *ba;

	ba = malloc(sizeof(struct bitarray));
	if (ba == NULL) {
		fprintf(stderr, "cba_alloc(): out of memory\n");
		exit(1);
	}

	if (bits <= 0) {
		ba->bits = 0;
		ba->array_sz = 0;
		ba->array = NULL;
	} else {
		ba->bits = bits;
		ba->array_sz = uint_array_size(bits);
		ba->array = calloc(ba->array_sz, sizeof(unsigned int));
		if (ba->array == NULL) {
			fprintf(stderr, "cba_alloc(): out of memory\n");
			exit(1);
		}
	}
	return ba;
}


void
cba_free(struct bitarray *ba)
{
	if (ba && ba->array) {
		free(ba->array);
	}
	free(ba);
}


long
cba_size(struct bitarray *ba)
{
	return ba->bits;
}


int
cba_getbit(struct bitarray *ba, long i)
{
	unsigned int b;

	i = index(ba, i);
	if (i < 0) return -1;
	b = ba->array[i / UINT_BITS] & bitmask(i);
	return (b > 0) ? 1 : 0;
}
