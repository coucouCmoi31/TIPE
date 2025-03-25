#ifndef objet_simu
#define objet_simu = 10

#include <SDL2/SDL.h>
#include "objets_graphique.c"
#include "objets_maths.h"

/*toutes les structures sont dans le tas*/
struct bloc_ecran;
typedef struct bloc_ecran bloc_ecran_t;

struct obj_sph;
typedef struct obj_sph obj_sph_t;

/*cree un bloc pour l'ecran d'origine A en de plan de centre B de dimention h et l en px*/
bloc_ecran_t* sp_ecran(pt_t* A, pt_t* B, int fen_px_h, int fen_px_l);

obj_sph_t* sp_obj_sph(sph_t* sph, SDL_Color c);

void free_obj_shp(obj_sph_t* sphere);

void free_bloc_ecran(bloc_ecran_t* e);

#endif
