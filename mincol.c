/* MINCOL 22-5-26 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "mincol.h"

//XVIDEO

#define PIXDIM 4 //dimension del pixel

typedef XPoint X_Point;
typedef long unsigned int X_Color;

X_Color X_BLACK=0;
X_Color X_WHITE=0;

uint16_t X_WINW=CARW*CARD*PIXDIM;
uint16_t X_WINH=CARH*CARD*PIXDIM;
static Display* display=NULL;
static Colormap colormap;
static Window window;
static Pixmap virtual;
static GC graphic;
static X_Color background;
static int min_key_code=0;
static int max_key_code=0;

X_Color x_color(double red,double green,double blue);

void x_flush();

int x_init() {
	int screenum=0;
	display=XOpenDisplay(0);
	if(display) {
		int screennum=XDefaultScreen(display);
		colormap=XDefaultColormap(display,screenum);
		X_BLACK=x_color(0,0,0);
		X_WHITE=x_color(1,1,1);
		window=XCreateSimpleWindow(display,RootWindow(display,screennum),0,0,X_WINW,X_WINH,0,0,0);
		XWindowAttributes xwa;
		XGetWindowAttributes(display,window,&xwa);
		virtual=XCreatePixmap(display,window,X_WINW,X_WINH,xwa.depth);
		static XGCValues gv;
		gv.line_width=1;
		gv.foreground=X_WHITE;
		gv.background=background=X_BLACK;
		graphic=XCreateGC(display,window,GCForeground|GCBackground|GCLineWidth,&gv);
		XSelectInput(display,window,StructureNotifyMask);
		XMapWindow(display,window);
		XEvent event;
		int mapped=0;
		while(XEventsQueued(display,QueuedAlready) || !mapped) {
			XNextEvent(display,&event);
			mapped=(!mapped)?(event.type==MapNotify):1;
		}
		XDisplayKeycodes(display,&min_key_code,&max_key_code);
		XSetForeground(display,graphic,gv.background);
		XFillRectangle(display,virtual,graphic,0,0,X_WINW,X_WINH);
		x_flush();
		return 1;
	}
	return 0;
}

void x_end() {
	XUnmapWindow(display,window);
	XDestroyWindow(display,window);
	XFreePixmap(display,virtual);
	XFreeColormap(display,colormap);
	XFreeGC(display,graphic);
	XEvent e;
	while(XEventsQueued(display,QueuedAlready)) {
			XNextEvent(display,&e);
	}
	XCloseDisplay(display);
}

X_Color x_color(double r,double g,double b) {
	const double FAC=65535;
	XColor xc;
	xc.flags=DoRed|DoGreen|DoBlue;
	xc.red=FAC*r;
	xc.green=FAC*g;
	xc.blue=FAC*b;
	XAllocColor(display,colormap,&xc);
	return xc.pixel;
}

#define inxwin(X,Y) ((X)>=0 && (X)<X_WINW && (Y)>=0 && (Y)<X_WINH)

void x_foreground(X_Color c) {
     XSetForeground(display,graphic,c);
}

void x_pixel(short x,short y) {
    if(inxwin(x,y)) {
           XDrawPoint(display,virtual,graphic,x,y);
    }
}

void x_flush() {
	XCopyArea(display,virtual,window,graphic,0,0,X_WINW,X_WINH,0,0);
	while(XPending(display)==0);
	XFlush(display);
}

int x_inkey(KeySym* keysym) {
	const int KCC=1;
	const unsigned char POS=0;
	int return_type=0;
	XEvent event;
	long event_mask=KeyPressMask|KeyReleaseMask;
	XSelectInput(display,window,event_mask);
	if(XPending(display)>0 && XCheckMaskEvent(display,event_mask,&event)) {
		int counter=0;
		XKeyEvent kevent=event.xkey;
		if(kevent.keycode>=min_key_code && kevent.keycode+KCC-1<=max_key_code) {
			KeySym* ks=XGetKeyboardMapping(display,kevent.keycode,KCC,&counter);
			if(POS<KCC*counter) {
				return_type=(kevent.type==KeyPress)?1:(kevent.type==KeyRelease)?-1:0;
				*keysym=*(ks+POS);
			}
			XFree(ks);
		}
	}
	return return_type;
}

//COLOR

Color colnew(double r,double g,double b) {
    return x_color(r,g,b);
}

//SPRITE

static uint16_t datalen(char* d) {
    // cuenta la longitud de datos validos  
    uint16_t counter=0;
    char* pd=d;
    while(*pd!='\0') {
        uint8_t val=*pd++-'0';
        if(val>0 && val<=PALDIM) counter++;
    }
    return counter;
}       

Sprite sprnew(Palette p,uint8_t w,uint8_t h,char* d) {
    uint16_t dl=datalen(d);
    Sprite s={p,w,h,dl,NULL};
    if(dl) {
        if((s.pix=malloc(sizeof(Pixel)*dl))) {
            char* pd=d;
            uint16_t count=0;
            Pixel* ppix=s.pix;
            while(*pd!='\0') {
                uint8_t c=(*pd)-'0';
                if(c>=0 && c<=PALDIM) {
                    if(c>0) {
                        uint8_t x=count%w;
                        uint8_t y=count/w;
                        Pixel p={x,y,c-1};
                        *ppix++=p;
                    }
                    count++;
                }
                pd++;
            }
        } else {
            s.w=s.h=0;
            s.pixs=0;
        }
    }
    return s;
}

void sprdel(Sprite* s) {
    if(s) {
        free(s->pix);
        s->pix=NULL;
        s->pixs=0;
        s->w=s->h=0;
        s->pal=NULL;
    }
}

void sprdrw(Sprite s,int16_t x,int16_t y) {
    Pixel* pp=s.pix;
    if(inxwin((x*PIXDIM),(y*PIXDIM))) {
        while(pp!=s.pix+s.pixs) {
            int32_t px=(x+pp->x)*PIXDIM;
            int32_t py=(y+pp->y)*PIXDIM;
            if(inxwin(px,py)) {
                x_foreground(s.pal[pp->cc]);
                for(int32_t ay=0;ay<PIXDIM;ay++) {
                    for(int32_t ax=0;ax<=PIXDIM/2;ax++) {
                        int32_t fx=(ay%2);
                        x_pixel(px+ax*2+fx,py+ay);
                    }
                }
            }
            pp++;
        }
    }
}

//PRUEBA

int main() {
    x_init();
    Palette p={colnew(1,0,0),colnew(0.5,0,0)};
    char* data="00111100 01111110 11111111 22222222 21111222 21122222 02222220 00222200";
    Sprite s=sprnew(p,8,8,data);
    sprdrw(s,10,10);
    x_flush();
    getchar();
    sprdel(&s);
    x_end();
}









            


    




