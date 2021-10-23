#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include </usr/include/signal.h>
#include <sys/time.h>
#include "assert.h"
#include "mem.h"
#include "sem.h"
#include "thread.h"

void _MONITOR(void) { }
extern void _ENDMONITOR(void);

/* thread implementation */
#define T Thread_T
/* macros */

/* types */
struct T {
	unsigned long *sp; // must be first
};

/* data */
static T ready = NULL;

/* prototypes */

/* static functions */

/* thread functions */

#undef T // Thread_T

/* sem implementation */
#define T Sem_T

/* sem functions */

#undef T // Sem_T
