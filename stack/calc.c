#include <stdio.h>
#include "stack.h"

int main(int argc, char **argv)
{
	Stack_T numbers;
	numbers = Stack_new();
	Stack_free(numbers);
	printf("everything is ok\n");
	return 0;
}

//extern T     Stack_new  (void);
//extern int   Stack_empty(T stk);
//extern void  Stack_push (T stk, void *x);
//extern void *Stack_pop  (T stk);
//extern void  Stack_free (T *stk);
