#include "ctimer.h"

void 
show(union sigval sv)
{
	printf("Timer expired: %d\n", sv.sival_int);
}

int
main(void)
{
	timer_t         tid;
	struct timespec ts;

	ctimeinit();

	ts.tv_sec  = 2;
	ts.tv_nsec = 0;

	tid = createcbtimer(ts, TRUE, show, (union sigval)2);
	if(tid == NULL)
		return -1;
	starttimer(tid);

	while(1){
		
	}

	return 0;
}
