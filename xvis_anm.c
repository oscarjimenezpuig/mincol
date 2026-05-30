/* XVIS_ANM 30-5-26 */

#include <stdlib.h>

#include "xvis_anm.h"

Animation anmnew(uint8_t clc,uint8_t mdl,uint8_t sprs,Sprite* spr[]) {
    Animation a={{0,0},{0,0},NULL};
    if(sprs && (a.spr=malloc(sizeof(Sprite*)*(sprs+1)))) {
        a.ptr=0;
        a.clc=(clc==0)?0:1;
        a.lim=(mdl>15)?15:mdl;
        a.dly=a.lim;
        Sprite** ptr=a.spr;
        Sprite** pro=spr;
        while(pro!=spr+sprs) {
            *ptr++=*pro++;
        }
        *ptr=NULL;
    }
    return a;
}

void anmdel(Animation* a) {
    if(a) {
        free(a->spr);
        *a=(Animation){{0,0},{0,0},NULL};
    }
}

void anmini(Animation* a) {
    if(a) {
        a->ptr=a->dly=0;
    }
}

uint8_t anmact(Animation* a,Sprite** s) {
    if(a && a->spr) {
        if(a->dly==a->lim) {
            *s=a->spr[a->ptr];
            if(*s) {
                a->dly=0;
                a->ptr++;
                return 1;
            } else {
                if(a->clc) {
                    a->ptr=0;
                    return anmact(a,s);
                }
            }
        } else {
            a->dly++;
        }
    }
    return 0;
}

uint8_t anmend(Animation a) {
    return (a.clc==0 && a.spr[a.ptr]==NULL);
}
            

    
