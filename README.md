## timeutil

Some functions  which are used to generate regular time format, or other stuff. For now, you can use those api to get time.

```c
char*   ymd(void);
char*   hms(void);
char*   timestampstr(void);
int64_t timestamp(void);
int64_t timestampwall(void);
int64_t timestampcpu(void);
```
The `timestampcpu` will support `ns`, but it return the `μs`. 

### Attention

Those functions are **not reentrant**. So when you use those int multiple thread project, that will be in a mess. And the reentrant version will be add later.

## timer

Timer is a set of wrap functions which use POSIX per-proccess timer. Now provide those API for create a callback timer( signaled timer will support later)

```c
void    ctimeinit(void);
timer_t createcbtimer(struct timespec, u8, callback, union sigval);
int     starttimer(timer_t);
int     stoptimer(timer_t);
int 	deletetimer(timer_t);
int     modifytimer(timer_t, struct timespec, u8);
```

The structure `sturct timespec` is defined in `time.h`, and `union sigval` is defined in `signal.h`. Here are the definition of those types:

```c
struct timespec{
	time_t  tv_sec;
	long    tv_nsec;
}

union sigval {
	int 	sival_int;
	void   *sival_ptr;
}
```

And the `callback` is a function pointer which defined by `sigevent`.

```c
void (*callback)(union sigval);
```

And when you want to create a period timer, you can set the second paramater of `createcbtimer` to `TRUE`.
## Example

Here is an example:

```c 
void show(union sigval arg)
{
	printf("CB: Expired at %ds\n", arg.sival_int);
}

int mian(void)
{
	struct timespec ts;
	timer_t         tid;

	ctimeinit();
	ts.tv_sec  = 2; /* 2s expired */
	ts.tv_nsec = 0;

	/* create a period timer */
	tid = createcbtimer(ts, TRUE, show, (union sigval)2);

	if(tid == NULL) return -1;
	starttimer(tid);

	while(1){ /*do nothing*/}
	return 0;
}
```

This example will print the result:

```shell
CB: Expired at 2s
CB: Expired at 2s
CB: Expired at 2s
CB: Expired at 2s
CB: Expired at 2s
^C
```
More example you can see [here](https://github.com/JesseEisen/timeutil/blob/master/timer/example.c)


(MIT)
