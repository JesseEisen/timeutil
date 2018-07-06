#include "ctimer.h"

typedef void (*callback)(union sigval);

void 
show(union sigval sv)
{
	printf("Timer expired: %d\n", sv.sival_int);
}

timer_t 
timercreate(callback cb)
{
	timer_t         timerid;
	struct sigevent sevp;

	memset(&sevp, 0, sizeof(struct sigevent));

	sevp.sigev_value.sival_int  = 2; 
	sevp.sigev_notify = SIGEV_THREAD;
	sevp.sigev_notify_function = cb;

	if(timer_create(CLOCK_REALTIME, &sevp, &timerid) < 0){
		if(errno == EINVAL)
			printf("timer_create error: %s\n", strerror(errno));
		return NULL;
	}

	return timerid;
}


int
timerstart(timer_t tid, time_t expr)
{
	struct itimerspec  it;
	
	it.it_value.tv_sec     = expr;
	it.it_value.tv_nsec    = 0;
	it.it_interval.tv_sec  = 0;
	it.it_interval.tv_nsec = 0;

	timer_settime(tid, 0, &it, NULL);
}


int
main(void)
{
	timer_t  tid;

	tid = timercreate(show);
	if(tid == NULL)
		return -1;
	timerstart(tid, 2);

	while(1){
		
	}

	return 0;
}


