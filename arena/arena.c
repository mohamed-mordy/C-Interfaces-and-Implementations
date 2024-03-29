#include <stdlib.h>
#include <string.h>
#include "arena.h"
#include "assert.h"
#include "except.h"

#define T Arena_T

const Except_T Arena_NewFailed = {
	"Arena Creation Aailed"
};
const Except_T Arena_Failed = {
	"Arena Allocation Aailed"
};

// macors
#define THRESHOLD 10

// types
struct T{
	T prev;
	char *avail;
	char *limit;
};

union align{
	int i;
	long l;
	long *lp;
	void *p;
	void (*fp)(void);
	float f;
	double d;
	long double ld;
};

union header{
	struct T b;
	union align a;
};

// data
static T freechunks;
static int nfree;

// functions
T Arena_new(void)
{
	T arena = malloc(sizeof (*arena));
	if(arena == NULL)
		RAISE(Arena_NewFailed);
	arena->prev = NULL;
	arena->limit = arena->avail = NULL;
	return arena;
}

void Arena_dispose(T *ap)
{
	assert(ap && *ap);
	Arena_free(*ap);
	free(*ap);
	*ap = NULL;
}

void *Arena_alloc(T arena, long nbytes, const char *file, int line)
{
	assert(arena);
	assert(nbytes > 0);
	//<round nbytes upto an alignment boundary>
	nbytes = ((nbytes + sizeof (union align) - 1)/
		(sizeof (union align))) *(sizeof (union align));
	// endof <>
	while(nbytes > arena->limit - arena->avail)
	{
		//<get a new chunk>
		T ptr;
		char *limit;
		//<ptr<--- a new chunk>
		if((ptr = freechunks) != NULL)
		{
			freechunks = freechunks->prev;
			nfree--;
			limit = ptr->limit;
		}
		else
		{
			long m = sizeof (union header) + nbytes + 10*1024;
			ptr = malloc(m);
			if(ptr == NULL)
			//<raise Arena_Failed
			{
				if(file == NULL)
					RAISE(Arena_Failed);
				else
				Except_raise(&Arena_Failed, file, line);
			}
			// endof<>
			limit = (char*)ptr + m;
		}
		// endof <>
		*ptr = *arena;
		arena->avail = (char *)((union header *)ptr + 1);
		arena->limit = limit;
		arena->prev = ptr;
		// endof <>
	}
	arena->avail += nbytes;
	return arena->avail - nbytes;
}

void *Arena_calloc(T arena, long count, long nbytes, const char *file, int line)
{
	void *ptr;
	//
	assert(count > 0);
	ptr = Arena_alloc(arena, count*nbytes, file, line);
	memset(ptr, '\0', count*nbytes);
	return ptr;
}

void Arena_free(T arena)
{
	assert(arena);
	while(arena->prev)
	{
		struct T tmp = *arena->prev;
		//<free the chunk described by arena>
		if(nfree < THRESHOLD)
		{
			arena->prev->prev = freechunks;
			freechunks = arena->prev;
			nfree++;
			freechunks->limit = arena->limit;
		}
		else
			free(arena->prev);
		// endof <>
		*arena = tmp;
	}
	assert(arena->limit == NULL);
	assert(arena->prev == NULL);
}
