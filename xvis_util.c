/* XVIS_UTIL 28-5-26 */

#include <stdlib.h>
#include <time.h>

#include "xvis_util.h"

int16_t maxim(int16_t a,int16_t b) {
    return (a>b)?a:b;
}

int16_t minim(int16_t a,int16_t b) {
    return (a<b)?a:b;
}

void seed(int16_t s) {
    if(s>=0) srand(s);
    else srand(time(NULL));
}

int16_t rnd(int16_t a,int16_t b) {
    int16_t max=maxim(a,b);
    int16_t min=minim(a,b);
    int16_t dif=max-min+1;
    return min+rand()%dif;
}

void pause(double t) {
    clock_t end=clock()+CLOCKS_PER_SEC*t;
    while(clock()<end);
}


