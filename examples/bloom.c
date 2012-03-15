/* A simple Bloom Filter example. */

#include "cba.h"
#include <stdio.h>

struct bloom {
	long m;     /* Size of the filter. */
	int k;      /* Number of hashes. */
	struct bitarray *ba;
};

void
init_bloom(struct bloom *bl, long m, int k)
{
	bl->m = m;
	bl->k = k;
	bl->ba = cba_alloc(m);
}


void
free_bloom(struct bloom *bl)
{
	if (bl->ba) {
		cba_free(bl->ba);
	}
}


long
hash1(const char *s, long sz)
{
	long h;

	/* DJB2 hash */
	for (h = 5381; *s != '\0'; s++) {
		h = ((h << 5) + h) + (long)*s;
	}

	return h % sz;
}


long
hash2(const char *s, long sz)
{
	long h;

	/* K&R 2e hash */
	for (h = 0; *s != '\0'; s++) {
		h = (long)*s + 31 * h;
	}
	return h % sz;
}


void
insert(struct bloom *bl, const char *s)
{
	long h1, h2, h;
	int i;

	h1 = h2 = 0;

	if (bl->k >= 1) {
		h1 = hash1(s, bl->m);
		cba_set(bl->ba, h1);
	}
	if (bl->k >= 2) {
		h2 = hash2(s, bl->m);
		cba_set(bl->ba, h2);
	}
	for (i = 1; i <= bl->k - 2; i++) {
		h = (h1 + i * h2) % bl->m;
		cba_set(bl->ba, h);
	}
}


int
lookup(struct bloom *bl, const char *s)
{
	long h1, h2;
	int i;

	h1 = h2 = 0;

	if (bl->k >= 1) {
		h1 = hash1(s, bl->m);

		if (!cba_get(bl->ba, h1)) {
			return 0;
		}
	}
	if (bl->k >= 2) {
		h2 = hash2(s, bl->m);
		if (!cba_get(bl->ba, h2)) {
			return 0;
		}
	}
	for (i = 1; i <= bl->k - 2; i++) {
		if (!cba_get(bl->ba, (h1 + i * h2) % bl->m)) {
			return 0;
		}
	}
	return 1;
}


int
main(void)
{
	struct bloom bl;
	init_bloom(&bl, 1000, 4);

	insert(&bl, "Abracadabra");
	if (lookup(&bl, "Abracadabra")) {
		printf("Abracadabra!\n");
	}
	if (lookup(&bl, "Alacazzam")) {
		printf("Alacazzam!\n");
	}

	free_bloom(&bl);
	return 0;
}
