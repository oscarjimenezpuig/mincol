/* XVIS_COL 31-5-26 */

#include "xvis_col.h"

Color BLACK, NAVY, DARK_BLUE, BLUE;
Color DARK_GREEN, DARK_TEAL, STEEL_BLUE, SKY_BLUE;
Color GREEN, SEA_GREEN, TURQUOISE, LIGHT_CYAN;
Color LIME, BRIGHT_LIME, AQUAMARINE, CYAN;
Color MAROON, DARK_PURPLE, DEEP_VIOLET, INDIGO;
Color DARK_OLIVE, DARK_GRAY, SLATE_BLUE, PERIWINKLE;
Color OLIVE_GREEN, SAGE_GREEN, SEAFOAM, LIGHT_SKY_BLUE;
Color YELLOW_GREEN, LIGHT_GREEN, MINT_GREEN, PALE_CYAN;
Color DARK_RED, DARK_MAGENTA, PURPLE, VIOLET;
Color BROWN, ROSY_BROWN, MAUVE, LAVENDER;
Color MUSTARD, KHAKI, LIGHT_GRAY, PALE_BLUE;
Color LIME_YELLOW, YELLOW_GREEN_LIGHT, PASTEL_GREEN, PALE_SKY_BLUE;
Color RED, HOT_PINK, FUCHSIA, MAGENTA;
Color ORANGE_RED, SALMON, PINK, ORCHID;
Color ORANGE, PEACH, LIGHT_PINK, PALE_PINK;
Color YELLOW, LIGHT_YELLOW, CREAM, WHITE;

static Color coldef(double r,double g,double b) {
    const double FAC=255.0;
    return colnew(r/FAC,g/FAC,b/FAC);
}

void csfini() {
    BLACK = coldef(0,0,0);
    NAVY = coldef(0,0,85);
    DARK_BLUE = coldef(0,0,170);
    BLUE = coldef(0,0,255);
    DARK_GREEN = coldef(0,85,0);
    DARK_TEAL = coldef(0,85,85);
    STEEL_BLUE = coldef(0,85,170);
    SKY_BLUE = coldef(0,85,255);
    GREEN = coldef(0,170,0);
    SEA_GREEN = coldef(0,170,85);
    TURQUOISE = coldef(0,170,170);
    LIGHT_CYAN = coldef(0,170,255);
    LIME = coldef(0,255,0);
    BRIGHT_LIME = coldef(0,255,85);
    AQUAMARINE = coldef(0,255,170);
    CYAN = coldef(0,255,255);
    MAROON = coldef(85,0,0);
    DARK_PURPLE = coldef(85,0,85);
    DEEP_VIOLET = coldef(85,0,170);
    INDIGO = coldef(85,0,255);
    DARK_OLIVE = coldef(85,85,0);
    DARK_GRAY = coldef(85,85,85);
    SLATE_BLUE = coldef(85,85,170);
    PERIWINKLE = coldef(85,85,255);
    OLIVE_GREEN = coldef(85,170,0);
    SAGE_GREEN = coldef(85,170,85);
    SEAFOAM = coldef(85,170,170);
    LIGHT_SKY_BLUE = coldef(85,170,255);
    YELLOW_GREEN = coldef(85,255,0);
    LIGHT_GREEN = coldef(85,255,85);
    MINT_GREEN = coldef(85,255,170);
    PALE_CYAN = coldef(85,255,255);
    DARK_RED = coldef(170,0,0);
    DARK_MAGENTA = coldef(170,0,85);
    PURPLE = coldef(170,0,170);
    VIOLET = coldef(170,0,255);
    BROWN = coldef(170,85,0);
    ROSY_BROWN = coldef(170,85,85);
    MAUVE = coldef(170,85,170);
    LAVENDER = coldef(170,85,255);
    MUSTARD = coldef(170,170,0);
    KHAKI = coldef(170,170,85);
    LIGHT_GRAY = coldef(170,170,170);
    PALE_BLUE = coldef(170,170,255);
    LIME_YELLOW = coldef(170,255,0);
    YELLOW_GREEN_LIGHT = coldef(170,255,85);
    PASTEL_GREEN = coldef(170,255,170);
    PALE_SKY_BLUE = coldef(170,255,255);
    RED = coldef(255,0,0);
    HOT_PINK = coldef(255,0,85);
    FUCHSIA = coldef(255,0,170);
    MAGENTA = coldef(255,0,255);
    ORANGE_RED = coldef(255,85,0);
    SALMON = coldef(255,85,85);
    PINK = coldef(255,85,170);
    ORCHID = coldef(255,85,255);
    ORANGE = coldef(255,170,0);
    PEACH = coldef(255,170,85);
    LIGHT_PINK = coldef(255,170,170);
    PALE_PINK = coldef(255,170,255);
    YELLOW = coldef(255,255,0);
    LIGHT_YELLOW = coldef(255,255,85);
    CREAM = coldef(255,255,170);
    WHITE = coldef(255,255,255);
}

//PRUEBA

#include "xvis_anm.h"
#include "xvis_util.h"
#include "xvis_spr.h"

int main() {
   winini();
   csfini();
   Palette p={BROWN,SALMON,ORCHID};
   Sprite sa=sprnew(p,8,8,"00012000 00012000 11112233 11222333 00023000 00023000 00033000 00033000");
   Sprite sb=sprrot(sa,1);
   Sprite sc=sprrot(sb,1);
   Sprite sd=sprrot(sc,1);
   Sprite* spr[]={&sa,&sb,&sc,&sd};
   Animation an=anmnew(1,5,4,spr);
   uint8_t end=0;
   while(!end) {
       if(keylst() && keyink('f')) end=1;
       Sprite* s;
       anmact(&an,&s);
       if(s) sprdrw(*s,20,20);
       winfls();
       pause(0.1);
       wincls();
   }
   sprdel(&sa);
   sprdel(&sb);
   sprdel(&sc);
   sprdel(&sd);
   anmdel(&an);
   winend();
}



