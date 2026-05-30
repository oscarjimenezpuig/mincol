/* XVIS 225-26 */

//Libreria encargada de la generacion de ventanas, sprites y deteccion de teclas

#ifndef XVIS
#define XVIS

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

typedef struct {
    int16_t x,y;
    uint16_t w,h;
} Rectangle;
//Rectangle: Definicion de un rectangulo


//FUNCIONES

Color colnew(double r,double g,double b);
//definicion de un nuevo color, necesario que este definida la ventana

void winini();
//inicio de la ventana

void winend();
//cerrado de la ventana

void winfls();
//flush

void winbkg(Color color);
//establecemos el color del background

void wincls();
//borramos toda la ventana y establecemos el color del background

Sprite sprnew(Palette palette,uint8_t w,uint8_t h,char* data);
//definicion de un sprite, data han de ser numero de 0 a 9, donde 0 representa
//el pixel vacio

Sprite sprcpy(Sprite s);
//copia un sprite

void sprdel(Sprite* s);
//se libera espacio del sprite

void sprdrw(Sprite s, int16_t x,int16_t y);
//imprime un sprite y lo coloca en una determinada posicion

void sprcls(Sprite s,int16_t x,int16_t y);
//borrado de un sprite que ocupa la posicion dicha

void sprpal(Sprite* s,Palette palette);
// cambia la paleta de un sprite

Rectangle recint(Rectangle a,Rectangle b);
//operacion que da el rectangulo interseccion de dos rectangulos

void recdrw(Rectangle r,Color c);
// dibuja el rectangulo relleno de color c

uint8_t keylst();
//se escucha a ver si hay alguna tecla que es pulsada o despulsada

uint8_t keyink(char a);
//mira si la tecla es pulsada o no

#endif //XVIS
