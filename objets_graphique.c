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

obj_plan_i* sp_obj_plan(plan_i* plan, SDL_Color c){
    obj_plan_i* Pl = malloc(sizeof(obj_plan_i));
    Pl->plan = plan;
    Pl->c = c;
    return Pl;
}

spirit_t* sp_spirit_vide(){
    spirit_t* s = malloc(sizeof(spirit_t));
    s->max_spirit = 16;
    s->list_sph = malloc(16*sizeof(obj_sph_t*));
    s->n_sph = 0;
    return s;
}

void agrandie_taille_max_spirit(spirit_t* s){
    if (s->n_sph + 1 >= s->max_spirit){
        s->max_spirit *= 2;
        s->list_sph = realloc(s->list_sph, s->max_spirit*sizeof(obj_sph_t*));
    }
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

void free_obj_plan(obj_plan_i* p){
    free_plan(p->plan);
    free(p);
}

void free_all_spirit(spirit_t* s){
    for (int i = 0; i<s->n_sph; i++){
        free_obj_shp(s->list_sph[i]);
    }
    free(s->list_sph);
    free(s);
}
