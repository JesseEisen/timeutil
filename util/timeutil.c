#include "timeutil.h"

static char result[3 + 1 + 3 + 1 + 20 + 1 + 20 + 1 + 20 + 1 + 20 + 1 + 20 + 1 + 1];
static char strts[30];

#ifdef CLOCK_MONOTONIC_RAW
#define CLOCKMONO  CLOCK_MONOTONIC_RAW
#else
#define CLOCKMONO  CLOCK_MONOTONIC
#endif

int64_t
timestampwall (void)
{
	struct timespec ts;
	clock_gettime (CLOCKMONO, &ts);
	return (int64_t) (ts.tv_sec + 1e-9 * ts.tv_nsec);
}

int64_t
timestampcpu (void)
{
	struct timespec ts;
	clock_gettime (CLOCK_PROCESS_CPUTIME_ID, &ts);
	return (int64_t) (ts.tv_sec + 1e-9 * ts.tv_nsec);
}

int64_t
timestamp (void)
{
	struct timeval tv;
	int ret;

	ret = gettimeofday (&tv, NULL);
	if (ret == -1)
		return -1;
	return (int64_t) ((int64_t) tv.tv_sec * 1000 + (int64_t) tv.tv_usec / 1000);
}

char *
ymd (void)
{
	struct timeval tv;
	int ret;

	ret = gettimeofday (&tv, NULL);
	if (ret == -1)
		return NULL;

	strftime (result, sizeof (result), "%Y.%m.%d", localtime (&tv.tv_sec));
	return result;
}

char *
hms (void)
{
	struct timeval tv;
	int ret;

	ret = gettimeofday (&tv, NULL);
	if (ret == -1)
		return NULL;

	strftime (result, sizeof (result), "%T", localtime (&tv.tv_sec));
	return result;

}

/* format: 12:34:56.789012 */
char *
timestampstr (void)
{
	struct timeval tv;
	int ret;

	ret = gettimeofday (&tv, NULL);
	if (ret == -1)
		return NULL;

	strftime (strts, sizeof (strts), "%T", localtime (&tv.tv_sec));
	snprintf (strts + 8, sizeof (strts) - 8, ".%6ld", tv.tv_usec);

	return strts;
}
