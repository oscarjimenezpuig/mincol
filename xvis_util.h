/* XVIS_UTIL 28-5-26 */

//Utilidades minimas para cualquier programa

#ifndef XVIS_UTIL
#define XVIS_UTIL

#include <stdint.h>

int16_t maxim(int16_t a,int16_t b);
// determina el maximo entre dos numeros

int16_t minim(int16_t a,int16_t b);
// determina el minimo entre dos numeros

void seed(int16_t seed);
//establece semilla de los aleatorios, si es negativa, depende del tiempo

int16_t rnd(int16_t a,int16_t b);
// numeros aleatorios entre a y b ambos incluidos

void pause(double time);
// se hace una pausa de un tiempo concreto

#endif //XVIS_UTIL


