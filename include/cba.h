#ifndef _CBA_H
#define _CBA_H

#include <limits.h>

#define UINT_BYTES (sizeof(unsigned int))
#define UINT_BITS (UINT_BYTES * CHAR_BIT)

/* Mask a particular bit within a uint. */
#define bitmask(bit) (1 << ((bit) % UINT_BITS))

/* Determine how many uints are needed to store a number of bits. */
#define uint_array_size(bits) (bits <= 0 ? 0 : (((bits) - 1) / UINT_BITS + 1))

struct bitarray;

struct bitarray *cba_alloc(long bits);
void cba_free(struct bitarray *ba);

long cba_size(struct bitarray *ba);
int cba_getbit(struct bitarray *ba, long i);

#endif
