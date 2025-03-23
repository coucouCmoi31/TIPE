#ifndef objet_simu
#define objet_simu = 10

#include <SDL2/SDL.h>
#include "objets_graphique.c"
#include "objets_maths.h"

typedef struct obj_sph{
    SDL_Color c;
    sph_t* sph;
} obj_sph_t;

/*toutes les structures sont dans le tas*/
struct bloc_ecran;
typedef struct bloc_ecran bloc_ecran_t;

/*cree un bloc pour l'ecran d'origine A en de plan de centre B de dimention h et l en px*/
bloc_ecran_t* sp_ecran(pt_t* A, pt_t* B, int fen_px_h, int fen_px_l);

void free_bloc_ecran(bloc_ecran_t* e);

#endif
