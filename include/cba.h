#ifndef _CBA_H
#define _CBA_H

struct bitarray;

struct bitarray *cba_alloc(long bits);
void cba_free(struct bitarray *ba);

/* Returns the size of ba in bits. */
long cba_size(struct bitarray *ba);

/* Gets the value of bit i in ba. Returns -1 on error. */
int cba_get(struct bitarray *ba, long i);

/* Sets bit i in ba. Returns 1 on success, -1 on error. */
int cba_set(struct bitarray *ba, long i);

/* Clears bit i in ba. Returns 1 on success, -1 on error. */
int cba_clear(struct bitarray *ba, long i);

#endif
