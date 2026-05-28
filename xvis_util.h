/* XVIS_UTIL 28-5-26 */

//Utilidades minimas para cualquier programa

#include <stdint.h>

typedef struct {
    int16_t x,y;
    uint16_t w,h;
} Rectangle;
//Rectangle: Definicion de un rectangulo

Rectangle recint(Rectangle a,Rectangle b);
//operacion que da el rectangulo interseccion de dos rectangulos

int16_t nummax(int16_t a,int16_t b);
// determina el maximo entre dos numeros

int16_t nummin(int16_t a,int16_t b);
// determina el minimo entre dos numeros

void rndsed(int16_t seed);
//establece semilla de los aleatorios, si es negativa, depende del tiempo

int16_t rndval(int16_t a,int16_t b);
// numeros aleatorios entre a y b ambos incluidos

void timpau(double time);
// se hace una pausa de un tiempo concreto
