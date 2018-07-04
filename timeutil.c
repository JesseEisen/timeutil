#include "timeutil.h"

static char result[3+1+ 3+1+20+1+20+1+20+1+20+1+20+1 + 1];

int64_t
timestamp(void)
{
    struct timeval tv;
    int ret;

    ret = gettimeofday(&tv, NULL);
    if(ret == -1) return -1;
    return (int64_t)((int64_t)tv.tv_sec * 1000 + (uint64_t)tv.tv_usec / 1000);
}

char *
ymd(void)
{
    struct timeval  tv;
    struct tm       *tm;

    gettimeofday(&tv, NULL);
    tm = localtime(&tv.tv_sec);

    strftime(result, sizeof(result), "%Y.%m.%d", tm);
    return result;
}
