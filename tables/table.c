#include <stddef.h>
#include <limits.h>
#include "mem.h"
#include "assert.h"
#include "table.h"

#define T Table_T

//<types>
struct T {
	//<fields>
	int size;
	int (*cmp)(const void *x, const void *y);
	unsigned (*hash)(const void *key);
	//endof<>
	struct binding {
		struct binding *link;
		const void *key;
		void *value;
	} **buckets;
};

//endof<>

//<static functions>
//endof<>

//<functions>
T Table_new(int hint,
	int cmp(const void *x, const void *y),
	unsigned hash(const void *key))
{
	T table;
	int i;
	static int primes[] = {
		509, 509, 1021, 2053, 4093,
		1819, 16381, 32771, 65521, INT_MAX
	};
	assert(hint >= 0);
	for(i = 1; primes[i] < hint; i++)
	;
	table = ALLOC(sizeof (*table) +
		primes[i - 1]*sizeof (table->buckets[0]));
	table->size = primes[i - 1];
	table->cmp  ? cmp  : cmpatom;
	table->hash ? hash : hashatom;
	table->buckets = (struct binding **)(table + 1);
	for(i = 0; i < table->size; i++)
		table->buckets[i] = NULL;
	table->length = 0;
	table->timestamp = 0;
	return table;
}
//endof<>
























