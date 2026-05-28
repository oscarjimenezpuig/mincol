/* XVIS_SPR 28-5-26 */

#include <stdlib.h>

#include "xvis_spr.h"

static uint8_t spralloc(Sprite* s,uint8_t w,uint8_t h,uint16_t pixs) {
    void* ptr=malloc(sizeof(Pixel)*pixs);
    if(ptr) {
        s->w=w;
        s->h=h;
        s->pixs=pixs;
        s->pix=ptr;
        return 1;
    }
    return 0;
}

static uint8_t refx(uint x,uint w) {
    return w-1-x;
}

static uint8_t refy(uint y,uint h) {
    return h-1-y;
}

Sprite sprref(Sprite s,Reflection r) {
    Sprite rs={s.pal,0,0,0,NULL};
    if(spralloc(&rs,s.w,s.h,s.pixs)) {
        Pixel* ps=s.pix;
        Pixel* pr=rs.pix;
        while(ps!=s.pix+s.pixs) {
            pr->x=(r & REFY)?refx(ps->x,s.w):ps->x;
            pr->y=(r & REFX)?refy(ps->y,s.h):ps->y;
            pr->cc=ps->cc;
            ps++;
            pr++;
        }
    }
    return rs;
}

//PRUEBA

int main() {
   winini();
   Color red=colnew(125,0,0);
   Color white=colnew(125,125,125);
   Palette p={red,white};
   char* data="11111000 11122000 11111000 11000000 11000000 11111200 10000000 11200000";
   Sprite s=sprnew(p,8,8,data);
   Sprite r=sprref(s,REFY|REFX);
   sprdrw(s,10,10);
   sprdrw(r,40,10);
   winfls();
   while(1) {
       keylst();
       if(keyink('f')) break;
   }
   sprdel(&s);
   sprdel(&r);
   winend();
}




    
