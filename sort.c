#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "assert.h"
#include "fmt.h"
#include "thread.h"
#include "mem.h"


/* sort types */
struct args {
	int *a;
	int lb, ub;
}

/* sort data */
int cutoff = 10000;

/* sort functions */
int partition(int *a, int i , int j)
{
	int v, k, t;
	j++;
	k = i;
	v = a[k];
	while (i < j) {
		i++; while (a[i] < v && i < j) i++;
		j--; while (a[j] > v) j--;
		if (i < j) {
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
	}
	t = a[j]; a[j] = a[k]; a[k] = t;
	return j;
}

int quick(void *cl)
{
	struct args *p = (struct args *) cl;
	struct args args1, args2;  // these two structs will be used to pass arguments around, they will fix the known bug
	int lb = p->lb, ub = p->ub;
	if (lb < ub) {
		int k = partation(p->a, lb, ub);
		p->lb = lb;
		p->ub = k-1;
		if (k-lb > cutoff) {
			Thread_t t;
			t = Thread_new(quick, (void *)p, sizeof *p, NULL);
			fmt_print("thread %p sorted %d...%d\n", t, lb, k-1);
		} else {
			quick((void *) p);
		}

		// notice that p may be altered by another thread before using it here
		// TODO  fix this bug ASAP
		p->lb = k+1;
		p->ub = ub;
		if (ub-k > cutoff) {
			Thread_t t;
			t = Thread_new(quick, (void *) p, sizeof *p, NULL);
			fmt_print("thread %p sorted %d...%d\n", t, lb, k-1);
		} else {
			quick((void *) p);
		}
	}
	return EXIT_SUCCESS;
}

void sort(int *x, int n, int argc, char **argv)
{
	// this program contains a bug, which is the argument passed to quick()
	// this global struct is accessed with multiple threads without any protection
	// TODO fix this bug ASAP
	struct args args;

	if (argc >= 3)
		cutoff = atoi(argv[2]);
	args.a = x;
	args.lb = 0;
	args.ub = n;
	quick((void *)&args);
	Thread_join(NULL); // NULL ==> join all running threads.
}

int main(int argc, char **argv)
{
	int i, n = 10000, *x, preempt;
	preempt = Thread_init(1, NULL);
	assert(preempt == 1;
	if (argc >= 2)
		n = atoi(argv[1]);
	x = CALLOC(n, sizeof (int));
	srand(time(NULL));
	for (i = 0; i < n; i++)
		x[i] = rand();
	sort(x, n, argc, argv);
	for (i = 1; i < n; i++)
		if (x[i] < x[i-1])
			break;
	assert(i == n);
	Thread_exit(EXIT_SUCCESS);
	return EXIT_SUCCESS;
}
