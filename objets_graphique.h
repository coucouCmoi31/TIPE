#ifndef objet_simu
#define objet_simu

#include <SDL2/SDL.h>
#include "objets_maths.h"

/*toutes les structures sont dans le tas*/
struct bloc_ecran{
    pt_t* A;
    plan_i* plan;
    int hp; /*la demi hauteur en px*/
    int lp; /*la demi largueur en px*/
};
typedef struct bloc_ecran bloc_ecran_t;

struct obj_sph{
    SDL_Color c;
    sph_t* sph;
};
typedef struct obj_sph obj_sph_t;

struct obj_plan
{
    SDL_Color c;
    plan_i* plan;
};
typedef struct obj_plan obj_plan_i;

struct spirit{
    int max_spirit;
    int n_sph;
    obj_sph_t** list_sph;
};
typedef struct spirit spirit_t;

/*cree un bloc pour l'ecran d'origine A en de plan de centre B de dimention h et l en px*/
bloc_ecran_t* sp_ecran(pt_t* A, pt_t* B, int fen_px_h, int fen_px_l);

obj_sph_t* sp_obj_sph(sph_t* sph, SDL_Color c);

obj_plan_i* sp_obj_plan(plan_i* plan, SDL_Color c);

spirit_t* sp_spirit_vide();

void agrandie_taille_max_spirit(spirit_t* s);

void deplace_ecran(bloc_ecran_t* e, float dx, float dy, float dz);

void free_obj_shp(obj_sph_t* sphere);

void free_bloc_ecran(bloc_ecran_t* e);

void free_obj_plan(obj_plan_i* p);

void free_all_spirit(spirit_t* s);

#endif
