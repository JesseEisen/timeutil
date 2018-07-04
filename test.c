#include "timeutil.h"

int
main(void)
{

    printf("Today:%15s\n", ymd());
    printf("right Now: %lld\n", timestamp());
    sleep(2);
    printf("2s  later: %lld\n", timestamp());

    return 0;
}
