#ifndef _CTIMER_H_
#define _CTIMER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include "list.h"

#define TRUE                       1
#define FALSE                      0
#define CTIME_MALLOC_TYPE(type)    (type *)malloc(sizeof(type))

typedef unsigned char   u8;
typedef void (*callback)(union sigval);

typedef struct Ctimer Ctimer;
struct Ctimer
{
	struct list_head  		 node;
	timer_t    		 		 tid;
	u8         		 		 isperiod;
	struct timespec  		 ts;
	callback   		 		 cb;
};

extern void    ctimeinit(void);
extern timer_t createcbtimer(struct timespec, u8, callback, union sigval);
extern int     starttimer(timer_t);


#endif
