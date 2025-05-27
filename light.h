#ifndef LIG
#define LIG = 10

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "objets_maths.h"

/*toutes les structures sont dans le tas*/
struct lumiere{
    float intensité;
    pt_t* position;
};
typedef struct lumiere lum_t;

/*le type sphere ou plan infini*/



/*des listes chainées de chaque type*/
struct maillon_lumiere {
    struct maillon_lumiere* suivant;
    lum_t* light;
};
typedef struct maillon_lumiere mai_lum_t;

struct liste_ch_lum{
    mai_lum_t* tete;
};
typedef struct liste_ch_lum ch_lum_t;

struct HSL{
    float H; //la couleur, entre 0 et 360
    float S; //saturation, entre 0 et 1
    float L; //luminosité, entre 0 et 1
};
typedef struct HSL HSL_t;

/*passe de RGB à HSL*/
HSL_t RGB_to_HSL(SDL_Color col);

SDL_Color HSL_to_RGB(HSL_t col);

/*valeur de la luminosité en un point: Calculs implémentés pour l'instant: 
X distance de la lumière
X scalaire avec l'angle lumière/normale
X reflet direct dans l'oeil
X lumière cachées (ombre) 
X multiples rebonds sur diverses surfaces (récursif) 
*/
/*pour un point à la surface d'une sphere*/
float point_lum_sph(pt_t* point, sph_t* sphe, ch_lum_t* lums, pt_t* camera);

/*pour un point à la surface d'un plan*/
/*avec ombres des sphères*/
float point_lum_pl(pt_t* point, plan_i* pl, ch_lum_t* lums, pt_t* camera, sph_t** spheres, int nb_sphe);




#endif