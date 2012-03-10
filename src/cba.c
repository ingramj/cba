#include "cba.h"
#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define UINT_BYTES (sizeof(unsigned int))
#define UINT_BITS (UINT_BYTES * CHAR_BIT)

/* Mask a particular bit within a uint. */
#define bitmask(bit) (1 << ((bit) % UINT_BITS))

/* Determine how many uints are needed to store a number of bits. */
#define uint_array_size(bits) (bits <= 0 ? 0 : (((bits) - 1) / UINT_BITS + 1))

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
cba_get(struct bitarray *ba, long i)
{
	unsigned int b;

	i = index(ba, i);
	if (i < 0) return -1;
	b = ba->array[i / UINT_BITS] & bitmask(i);
	return (b > 0) ? 1 : 0;
}


int
cba_set(struct bitarray *ba, long i)
{
	i = index(ba, i);
	if (i < 0) return -1;

	ba->array[i / UINT_BITS] |= bitmask(i);
	return 1;
}


void
cba_set_all(struct bitarray *ba)
{
	/* this test may not be necessary, but just in case... */
	if (ba && ba->array) {
		memset(ba->array, 0xff, (ba->array_sz * UINT_BYTES));
	}
}


int
cba_clear(struct bitarray *ba, long i)
{
	i = index(ba, i);
	if (i < 0) return -1;

	ba->array[i / UINT_BITS] &= ~bitmask(i);
	return 1;
}


void
cba_clear_all(struct bitarray *ba)
{
	if (ba && ba->array) {
		memset(ba->array, 0x00, (ba->array_sz * UINT_BYTES));
	}
}
