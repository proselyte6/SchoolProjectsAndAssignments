#include <sys/time.h>

extern struct timeval tvalStart, tvalEnd;

void startTimer();

void endTimer();

void calculateTimeDifference();