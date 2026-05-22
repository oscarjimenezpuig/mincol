/* MINCOL 22-5-26 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "mincol.h"

//XVIDEO

typedef XPoint X_Point;
typedef long unsigned int X_Color;

X_Color X_BLACK=0;
X_Color X_WHITE=0;

unsigned int X_WINW=0;
unsigned int X_WINH=0;
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

int x_init(unsigned int w,unsigned int h) {
	X_WINW=w;
	X_WINH=h;
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

void x_pixel(short x,short y,X_Color c) {
    XSetForeground(display,graphic,c);
    XDrawPoint(display,virtual,graphic,x,y);
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
    return (Color){r,g,b,x_color(r,g,b)};
}

//PALETTE

Palette palnew(unsigned char cs,...) {
    Palette p;
    va_list list;
    va_start(list,cs);
    for(int k=0;k<cs;k++) {
        p.col[k]=va_arg(list,Color);
    }
    va_end(list);
    for(int c=cs;c<PALDIM;c++) p.col[c]=(Color){0,0,0,X_BLACK};
    return p;
}

//SPRITE

#define PIXDIM 6 //tamaño de un pixel

static char dataget(unsigned char r,unsigned char c,unsigned char w,char* d) {
    //Da el dato que se encuentra en la fila r columna c
    return d[c+r*w]-'0';
}

static void datapos(unsigned short* r,unsigned short* c,unsigned char w,char* d,char* pd) {
    //Da la fila y la columna de un puntero a los datos
    *r=(pd-d)/w;
    *c=(pd-d)%w;
    *r*=PIXDIM;
    *c*=PIXDIM;
}

static char poralloc(Sprite* s,unsigned short x,unsigned short y,unsigned long c) {
    //realoca los puntos del sprite para dar cabida a los siguientes
    Point* ptr=realloc(s->po,sizeof(Point)+(s->pos+1));
    if(ptr) {
        s->po=ptr;
        s->po[s->pos++]=(Point){x,y,c};
        return 1;
    }
    return 0;
}

Sprite sprnew(Palette* p,unsigned char w,unsigned char h,char* d) {
    const int DXV[]={0,PIXDIM/2,(PIXDIM/2)+1,PIXDIM-1};
    const int DYUV[]={0,PIXDIM/2,(PIXDIM/2),0};
    const int DYDV[]={PIXDIM-1,(PIXDIM/2)+1,(PIXDIM/2)+1,PIXDIM-1};
    char* pd=d;
    Sprite s={p,w,h,0,NULL};
    while(*pd!='\0') {
        short cc=*pd-'0';
        if(cc>0 && cc<=9) {
            long unsigned int col=p->col[cc].cc;
            unsigned short x0,y0;
            datapos(&y0,&x0,w,d,pd);
            for(int k=0;k<4;k++) {
                poralloc(&s,x0+DXV[k],y0+DYUV[k],col);
                poralloc(&s,x0+DXV[k],y0+DYDV[k],col);
            }
        }
    }
    return s;
}

void sprdel(Sprite* s) {
    if(s) {
        free(s->po);
        s->po=NULL;
        s->pos=0;
        s->w=s->h=0;
        s->pal=NULL;
    }
}

void sprdrw(Sprite s,unsigned short r,unsigned short c) {
    Point* ppo=s.po;
    while(ppo!=s.po+s.pos) {
        x_pixel(c+ppo->x,r+ppo->y,ppo->col);
        ppo++;
    }
}









            


    




