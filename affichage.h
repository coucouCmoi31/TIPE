#ifndef aff_guard
#define aff_guard

#include <SDL2/SDL.h>
#include "objets_graphique.h"
#include "objets_maths.h"
#include "light.h"

/* met la couleur du pixel cx cy a color */
int MART_SetPixel(SDL_Renderer* renderer, int cx, int cy, SDL_Color color);

/* pour un pixel donner et une direction donner met le pixel a la couleur de sphere si il y a colision */
int MART_ColorSphereOnePixel(SDL_Renderer* renderer, int cx, int cy, obj_sph_t* sphere, pt_t* origine, vect_t* direction, ch_lum_t* leslumi);

/* affiche une sphere */
int Mart_ColorSphere(SDL_Renderer* renderer, obj_sph_t* sph, bloc_ecran_t* e, ch_lum_t* leslumi);

/* pour un pixel donner et une direction donner met le pixel a la couleur du plan si il y a colision */
int Mart_ColorPlanOnePixiel(SDL_Renderer* renderer, int cx, int cy, obj_plan_i* plan, pt_t* origine, vect_t* direction);

/* affiche un plan */
int Mart_ColorPlan(SDL_Renderer* renderer, obj_plan_i* pl, bloc_ecran_t* e);

int MART_ColorSpiritOnePixel(SDL_Renderer* renderer, int cx, int cy, spirit_t* spirit, pt_t* origine, vect_t* direction, ch_lum_t* leslumi);

int MART_ColorSpirit(SDL_Renderer* renderer, spirit_t* spirit, bloc_ecran_t* e, ch_lum_t* leslumi);

int MART_ColorSpiritLess(SDL_Renderer* renderer, spirit_t* spirit, bloc_ecran_t* e, ch_lum_t* leslumi);

#endif