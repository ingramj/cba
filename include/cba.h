#ifndef _CBA_H
#define _CBA_H

struct bitarray;

struct bitarray *cba_alloc(long bits);
void cba_free(struct bitarray *ba);

long cba_size(struct bitarray *ba);
int cba_getbit(struct bitarray *ba, long i);

#endif
