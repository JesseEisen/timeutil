#ifndef _TIMEUTIL_H_
#define _TIMEUTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

char*   ymd(void);
char*   hms(void);
char*   timestampstr(void);
int64_t timestamp(void);
int64_t timestampwall(void);
int64_t timestampcpu(void);


#endif
