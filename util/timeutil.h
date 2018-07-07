#ifndef _TIMEUTIL_H_
#define _TIMEUTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

extern char*   ymd(void);
extern char*   hms(void);
extern char*   timestampstr(void);
extern int64_t timestamp(void);
extern int64_t timestampwall(void);
extern int64_t timestampcpu(void);


#endif
