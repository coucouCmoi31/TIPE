#ifndef LIG
#define LIG = 10

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "objets_maths.h"

/*toutes les structures sont dans le tas*/
struct lumiere{
    float intensité;
    pt_t position;
};
typedef struct lumiere lum_t;

/*valeur de la luminosité en un point: Calculs implémentés pour l'instant: 
X distance de la lumière
X scalaire avec l'angle lumière/normale
X reflet direct dans l'oeil
X lumière cachées (ombre) 
X multiples rebonds sur diverses surfaces (récursif) 
*/
float point_lum()



#endif