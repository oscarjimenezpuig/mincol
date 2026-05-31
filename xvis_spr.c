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

static Pixel onerot(Pixel p,uint8_t h) {
    //rota el pixel una vez
    return (Pixel){h-p.y,p.x,p.cc};
}

Sprite sprrot(Sprite s,uint8_t rots) {
    Sprite rs={s.pal,0,0,0,NULL};
    uint8_t rsw=(rots%2)?s.h:s.w;
    uint8_t rsh=(rots%2)?s.w:s.h;
    if(spralloc(&rs,rsw,rsh,s.pixs)) {
        Pixel* ps=s.pix;
        Pixel* pr=rs.pix;
        while(ps!=s.pix+s.pixs) {
            *pr=*ps;
            for(int k=0;k<rots;k++) {
                *pr=onerot(*ps,s.h);
            }
            pr++;
            ps++;
        }
    }
    return rs;
}

static Pixel* pixamp(Pixel* r,Pixel p,uint8_t fact) {
    // se amplia un pixel y se devuelve el numero de pixels ampliados
    uint8_t pxi=p.x*fact;
    uint8_t pyi=p.y*fact;
    Pixel* pr=r;
    for(uint8_t px=pxi;px<pxi+fact;px++) {
        for(uint8_t py=pyi;py<pyi+fact;py++) {
            *pr++=(Pixel){px,py,p.cc};
        }
    }
    return pr;
}

Sprite spramp(Sprite s,uint8_t fact) {
    Sprite rs={s.pal,0,0,0,NULL};
    if(spralloc(&rs,s.w*fact,s.h*fact,s.pixs*fact*fact)) {
        Pixel* ps=s.pix;
        Pixel* pr=rs.pix;
        while(ps!=s.pix+s.pixs) pr=pixamp(pr,*ps++,fact);
    }
    return rs;
}


