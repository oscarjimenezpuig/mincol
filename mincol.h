/* MINCOL 225-26 */

#include <stdint.h>

//CONSTANTES

//constantes de pantalla
#define CARW 32 //numero de columnas de caracter
#define CARH 23 //numero de filas de caracter
#define CARD 8 //dimension de un caracter

//constantes de paleta
#define PALDIM 4 //dimension de la paleta

//constantes de entrada teclado
#define KEYDIM 4 //numero de teclas que pueden ser almacenadas a la vez

//TIPOS

typedef long unsigned int Color;
//Color: guarda la combinacion de colores asi como el codigo del color

typedef Color Palette[PALDIM];
//Palette: Coleccion de colores de un sprite

typedef struct {
    uint8_t x,y;
    uint8_t cc;
} Pixel;
//Pixel: x,y posicion del pixel, cc el codigo de color segun la paleta

typedef struct {
    Color* pal;
    uint8_t w,h;
    uint16_t pixs;
    Pixel* pix;
} Sprite;
//Sprite: dibujo compuesto por una cantidad de pixeles concreta

//FUNCIONES

Color colnew(double r,double g,double b);
//colnew: definicion de un nuevo color

Sprite sprnew(Palette palette,uint8_t w,uint8_t h,char* data);
//definicion de un sprite, data han de ser numero de 0 a 9, donde 0 representa
//el pixel vacio

void sprdel(Sprite* s);
//se libera espacio del sprite

void sprdrw(Sprite s, int16_t x,int16_t y);
//imprime un sprite y lo coloca en una determinada posicion
    
