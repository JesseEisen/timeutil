#include "timeutil.h"

int
main (void)
{
  printf ("\n");
  printf ("\tYMD: %26s\n", ymd ());
  printf ("\tHMS: %24s\n", hms ());
  printf ("\ttimestamp: %23lld\n", timestamp ());
  sleep (2);
  printf ("\ttimstamp(2s later): %14lld\n", timestamp ());
  printf ("\tstring stamp: %22s\n", timestampstr ());
  printf ("\n");


  printf ("\ttimeofcpu: %24lld\n", timestampcpu ());
  printf ("\ttimestamp: %23lld\n", timestamp ());
  sleep (2);
  printf ("\ttimeofwall: %24lld\n", timestampwall ());
  return 0;
}
