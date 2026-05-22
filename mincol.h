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
    unsigned char r,c;
    long unsigned int col;
} Pixel;
//Pixel: Componente de un sprite que contiene la posicion y el numero de color

typedef struct {
    unsigned char pal;
    unsigned char w,h;
    unsigned short pixs;
    Pixel* pix;
} Sprite;
//Sprite: dibujo compuesto por una cantidad de pixeles concreta

Color colnew(double r,double g,double b);
//colnew: definicion de un nuevo color

signed char palnew(unsigned char cols,...);
//definicion de una nueva paleta (devuelve el indice de referencia) se entra el numero de colores de la paleta hasta 9 maximo


