#include <stddef.h>
#include "assert.h"
#include "mem.h"
#include "stack.h"

#define T Stack_T

// types
struct T {
	int count;
	struct elem {
		void *x;
		struct elem *link;
	} *head;
};

// functions
T Stack_new(void)
{
	T stk;
	NEW(stk);
	stk->count = 0;
	stk->head = NULL;
	return stk;
}

int Stack_empty(T stk)
{
	assert(stk);
	return stk->count == 0;
}

void Stack_push(T stk, void *x)
{
	assert(stk);
	struct elem *t;
	NEW(t);
	t->x = x;
	t->link = stk->head;
	stk->head = t;
	stk->count++;
}

void *Stack_pop(T stk)
{
	assert(stk);
	assert(stk->count > 0);
	struct elem *t = stk->head;
	stk->head = t->link;
	stk->count--;
	void *x = t->x;
	FREE(t);
	return x;
}

void Stack_free(T *stk)
{
	assert(stk && *stk);
	for (struct elem *t = (*stk)->head, *u; t; t = u) {
		u = t->link;
		FREE(t);
	}
	FREE(*stk);
}

