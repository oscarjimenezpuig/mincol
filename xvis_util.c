/* XVIS_UTIL 28-5-26 */

#include <stdlib.h>
#include <time.h>

#include "xvis_util.h"

Rectangle recint(Rectangle a,Rectangle b) {
    Rectangle r;
    if(a.x<b.x) {
        r.x=a.x;
        r.w=(a.w>b.x)?a.w-b.x:0;
    } else {
        r.x=b.x;
        r.w=(b.w>a.x)?b.w-a.x:0;
    }
    if(a.y<b.y) {
        r.y=a.y;
        r.h=(a.h>b.y)?a.h-b.y:0;
    } else {
        r.y=b.y;
        r.h=(b.h>a.y)?b.h-a.y:0;
    }
    return r;
}

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


