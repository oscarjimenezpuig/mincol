/* MINCOL 225-26 */

#include <stdarg.h>

#define PALDIM 9 // dimension de la paleta
#define NULPAL -1 //valor que indica que el identificador de la paleta es nulo

typedef struct {
    double r,g,b;
    long unsigned int cc;
} Color;
//Color: guarda la combinacion de colores asi como el codigo del color

typedef struct {
    Color col[PALDIM];
} Palette;
//Paleta: guarda los colores (de 1 a 9) que se usaran en un sprite

typedef struct {
    unsigned short x,y;
    long unsigned int col;
} Point;
//Pixel: Componente de un sprite que contiene la posicion y el numero de color

typedef struct {
    Palette* pal;
    unsigned char w,h;
    unsigned short pos;
    Point* po;
} Sprite;
//Sprite: dibujo compuesto por una cantidad de pixeles concreta

Color colnew(double r,double g,double b);
//colnew: definicion de un nuevo color

Palette palnew(unsigned char cols,...);
//definicion de una nueva paleta (devuelve el indice de referencia) se entra el numero de colores de la paleta hasta 9 maximo

Sprite sprnew(Palette* palette,unsigned char w,unsigned char h,char* data);
//definicion de un sprite, data han de ser numero de 0 a 9, donde 0 representa
//el pixel vacio

void sprdel(Sprite* s);
//se libera espacio del sprite

void sprdrw(Sprite s,unsigned short r,unsigned short c) {
    
