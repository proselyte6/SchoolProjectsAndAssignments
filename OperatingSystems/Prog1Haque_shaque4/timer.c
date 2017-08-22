#include <stdio.h>
#include <sys/time.h>
#include "timer.h"

struct timeval tvalStart, tvalEnd;

void startTimer(){
    gettimeofday (&tvalStart, NULL);
}

void endTimer(){
    gettimeofday (&tvalEnd, NULL);
}

void calculateTimeDifference(){
    fprintf(stderr, "Elapsed Time: %ld microseconds\n",
           (tvalEnd.tv_sec - tvalStart.tv_sec)*1000000);
}