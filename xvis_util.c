/* XVIS_UTIL 28-5-26 */

#include <stdlib.h>
#include <time.h>

#include "xvis_util.h"

int16_t nummax(int16_t a,int16_t b) {
    return (a>b)?a:b;
}

int16_t nummin(int16_t a,int16_t b) {
    return (a<b)?a:b;
}

void rndsed(int16_t s) {
    if(s>=0) srand(s);
    else srand(time(NULL));
}

int16_t rndval(int16_t a,int16_t b) {
    int16_t max=nummax(a,b);
    int16_t min=nummin(a,b);
    int16_t dif=max-min+1;
    return min+rand()%dif;
}


