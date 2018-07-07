#include "ctimer.h"

static int count = 0;
static struct timespec ts;

void 
show(union sigval sv)
{
	count++;
	printf("Timer expired: %d, cb argument: %d\n", ts.tv_sec, sv.sival_int);
}

int
main(void)
{
	u8       bset = 0;
	timer_t  tid;

	ctimeinit();

	ts.tv_sec  = 2;
	ts.tv_nsec = 0;

	tid = createcbtimer(ts, TRUE, show, (union sigval)2);
	if(tid == NULL)
		return -1;
	starttimer(tid);

	while(1){
		if((count == 5) && (bset == 0)){
			ts.tv_sec  = 1;
			ts.tv_nsec = 0;
			modifytimer(tid, ts, TRUE);
			bset = 1;
			printf("modify timer length to 1s\n");
		}

		if(count == 8){
			stoptimer(tid);
			break;
		}
	}

	deletetimer(tid);
	printf("timer is deleted\n");

	return 0;
}
