/* MINCOL 225-26 */

#define PALDIM 9 /* dimension de la paleta */

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
    unsigned char ccol;
} Pixel;
//Pixel: Componente de un sprite que contiene la posicion y el numero de color de la paleta utilizada

typedef struct {
    unsigned char pal;
    unsigned char w,h;
    unsigned short pixs;
    Pixel* pix;
} Sprite;
/*Sprite: dibujo compuesto por una cantidad de pixeles concreta

