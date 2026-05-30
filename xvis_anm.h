/* XVIS_ANM 30-5-26 */

//Estructura para almacenar animacion sprite a sprite

#ifndef XVIS_ANM
#define XVIS_ANM

#include "xvis.h"

typedef struct {
    struct {
        uint8_t ptr : 7;
        uint8_t clc: 1;
    };
    struct {
        uint8_t dly : 4;
        uint8_t lim : 4;
    };
    Sprite** spr;
} Animation;

//La coleccion de sprites spr acaba siempre en NULL.
//prt: indica el numero del sprite apuntado (max 64)
//dly: delay antes de saltar a la siguiente animacion
//lim: momento en el que salta a la siguiente animacion
//clc: indica si la animacion es o no ciclica

Animation anmnew(uint8_t clc,uint8_t max_dly,uint8_t sprs,Sprite* spr[]);
//definicion de una nueva animacion diciendo si es ciclica, el numero de sprites y los sprites

void anmdel(Animation* a);
//liberamos el espacio de la animacion

void anmini(Animation* a);
//ponemos la animacion apuntando al primer sprite (dly se pone en 0)

uint8_t anmact(Animation* a,Sprite** s);
//se hace actuacion de animacion, si hay transicion el resultado es 1 y se pasa el sprite que toca
//si ha llegado al final o no hay transicion devuelve 0

uint8_t anmend(Animation a);
//dice si la animacion ha llegado al final

#endif //XVIS_ANM
