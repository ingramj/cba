#ifndef _CBA_H
#define _CBA_H

struct bitarray;

struct bitarray *cba_alloc(long bits);
void cba_free(struct bitarray *ba);

/* Return the size of ba in bits. */
long cba_size(struct bitarray *ba);

/* Get the value of bit i in ba. Return -1 on error. */
int cba_get(struct bitarray *ba, long i);

/* Set bit i in ba. Return 1 on success, -1 on error. */
int cba_set(struct bitarray *ba, long i);

/* Clear bit i in ba. Return 1 on success, -1 on error. */
int cba_clear(struct bitarray *ba, long i);

/* Set all bits in ba. */
void cba_set_all(struct bitarray *ba);

/* Clear all bits in ba. */
void cba_clear_all(struct bitarray *ba);

#endif
