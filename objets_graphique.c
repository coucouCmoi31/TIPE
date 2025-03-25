#include "objets_maths.h"
#include "objets_graphique.h"
#include <SDL2/SDL.h>

bloc_ecran_t* sp_ecran(pt_t* A, pt_t* B, int fen_px_h, int fen_px_l){
    bloc_ecran_t* e = malloc(sizeof(bloc_ecran_t));
    e->A = A;
    e->hp = fen_px_h/2;
    e->lp = fen_px_l/2;
    e->plan = sp_plan(vect_from_points(A, B), B);
    return e;
}

obj_sph_t* sp_obj_sph(sph_t* sph, SDL_Color c){
    obj_sph_t* Sh = malloc(sizeof(obj_sph_t));
    Sh->sph = sph;
    Sh->c = c;
    return Sh;
}


void free_bloc_ecran(bloc_ecran_t* e){
    free_plan(e->plan);
    free_pt(e->A);
    free(e);
}

void free_obj_shp(obj_sph_t* sphere){
    free_sph(sphere->sph);
    free(sphere);
}
