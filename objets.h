#ifndef objet_simu
#define objet_simu = 10

#include "ecran.c"
#include "objets_maths.h"

typedef struct color
{
    int r;
    int g;
    int b;
    int alpha; /*coef de transtarance de naturelement a 255 : pas transparent*/
} color_t;

typedef struct obj_sph{
    color_t* c;
    sph_t* sph;
} obj_sph_t;


#endif