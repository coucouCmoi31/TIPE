#ifndef aff_guard
#define aff_guard

#include <SDL2/SDL.h>
#include "objets_graphique.h"
#include "objets_maths.h"

int MART_SetPixel(SDL_Renderer* renderer, int cx, int cy, SDL_Color color);

int MART_ColorSphereOnePixel(SDL_Renderer* renderer, int cx, int cy, obj_sph_t* sphere, pt_t* origine, vect_t* direction);

int Mart_ColorSphere(SDL_Renderer* renderer, obj_sph_t* sph, bloc_ecran_t* e);


#endif