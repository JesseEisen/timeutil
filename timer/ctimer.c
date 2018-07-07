#include "ctimer.h"

struct list_head  timerlist;
static Ctimer * gettimerinfo(timer_t tid);

void ctimeinit(void)
{
	INIT_LIST_HEAD(&timerlist);
}

timer_t
createcbtimer(struct timespec ts, u8 isperiod, callback cb, union sigval arg)
{
	Ctimer 			*ct;
	timer_t   		tid;
	struct sigevent sevp;


	memset(&sevp, 0, sizeof(struct sigevent));

	sevp.sigev_value           =  arg;
	sevp.sigev_notify          =  SIGEV_THREAD;
	sevp.sigev_notify_function =  cb;

	if(timer_create(CLOCK_REALTIME, &sevp, &tid) < 0){
		fprintf(stderr, "timer_create error: %s\n", strerror(errno));
		return NULL;
	}

	ct = CTIME_MALLOC_TYPE(Ctimer);
	if(ct == NULL){
		fprintf(stderr, "malloc space error\n");
		return NULL;
	}

	ct->tid 	   = tid;
	ct->cb  	   = cb;
	ct->isperiod   = isperiod;
	ct->ts.tv_sec  = ts.tv_sec;
	ct->ts.tv_nsec = ts.tv_nsec;

	list_add(&ct->node, &timerlist);
	
	return tid;
}

static Ctimer *
gettimerinfo(timer_t tid)
{
	Ctimer *ct;

	list_for_each_entry(ct, &timerlist, node){
		if(ct->tid == tid)
			return ct;
	}

	return NULL;
}


int
starttimer(timer_t tid)
{
	Ctimer 			  *ct;
	struct itimerspec  it;

	ct = gettimerinfo(tid);
	if(ct == NULL){
		fprintf(stderr, "timer id not create\n");
		return -1;
	}

	it.it_value.tv_sec  = ct->ts.tv_sec;
	it.it_value.tv_nsec = ct->ts.tv_nsec;
	if(ct->isperiod == TRUE){
		it.it_interval.tv_sec  = ct->ts.tv_sec;
		it.it_interval.tv_nsec = ct->ts.tv_nsec;
	}

	timer_settime(tid, 0, &it, NULL);
}




