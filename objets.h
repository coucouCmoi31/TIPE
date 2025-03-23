#ifndef objet_simu
#define objet_simu = 10

#include <SDL2/SDL.h>
#include "ecran.c"
#include "objets_maths.h"

typedef struct obj_sph{
    SDL_Color c;
    sph_t* sph;
} obj_sph_t;


#endif
