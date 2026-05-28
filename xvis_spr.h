/* XVIS_SPR 28-5-26 */

//Libreria que sirve para hacer diversas operaciones con los sprites

#include "xvis.h"

typedef enum {NONE=0,REFX=1,REFY=2} Reflection;

Sprite sprref(Sprite s,Reflection r);
//Se crea un sprite simetrico con reflexiones respecto a X o Y o a las dos */


