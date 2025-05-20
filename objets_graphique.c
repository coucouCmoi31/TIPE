#include "objets_maths.h"
#include "objets_graphique.h"
#include "math.h"
#include <SDL2/SDL.h>

bloc_ecran_t* sp_ecran(pt_t* A, pt_t* B, int fen_px_h, int fen_px_l){
    bloc_ecran_t* e = malloc(sizeof(bloc_ecran_t));
    e->A = A;
    e->hp = fen_px_h/2;
    e->lp = fen_px_l/2;
    e->plan = sp_plan(vect_from_points(A, B), B);
    e->d = sqrtf(e->plan->n->vx*e->plan->n->vx + e->plan->n->vy*e->plan->n->vy + e->plan->n->vy*e->plan->n->vz);
    normalise_vect(e->plan->n);
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
    s->max_spirit_sph = 16;
    s->list_sph = malloc(16*sizeof(obj_sph_t*));
    s->n_sph = 0;
    s->max_spirit_plan = 16;
    s->list_plan = malloc(16*sizeof(obj_plan_i*));
    s->n_plan = 0;
    return s;
}

void agrandie_taille_max_spirit(spirit_t* s){
    if (s->n_sph + 1 >= s->max_spirit_sph){
        s->max_spirit_sph *= 2;
        s->list_sph = realloc(s->list_sph, s->max_spirit_sph*sizeof(obj_sph_t*));
    } if (s->n_plan+1 >= s->max_spirit_plan){
        s->max_spirit_plan *= 2;
        s->list_plan = realloc(s->list_plan, s->max_spirit_plan*sizeof(obj_plan_i*));
    }
}

void ajouter_shp_spirit(spirit_t* s, obj_sph_t* sph){
    agrandie_taille_max_spirit(s);
    s->list_sph[s->n_sph] = sph;
    s->n_sph += 1;
}

void ajouter_plan_spirit(spirit_t* s, obj_plan_i* plan){
    agrandie_taille_max_spirit(s);
    s->list_plan[s->n_plan] = plan;
    s->n_plan += 1;
}

void deplace_ecran(bloc_ecran_t* e, float dx, float dy, float dz){
    e->A->x += dx;
    e->A->y += dy;
    e->A->z += dz;
    e->plan->A->x += dx;
    e->plan->A->y += dy;
    e->plan->A->z += dz;
}

void deplace_ecran_vect(bloc_ecran_t* e, float n, float l, float h){
    vect_t* v_l = sp_vect(0, 0, 0);
    cr_vect_l(e->plan->n, v_l);
    normalise_vect(v_l);
    vect_t* v_h = sp_vect(0, 0, 0);
    cr_vect_h(e->plan->n, v_h);
    normalise_vect(v_h);

    deplace_ecran(e, e->plan->n->vx*n + v_l->vx*l + v_h->vx*h, e->plan->n->vy*n + v_l->vy*l + v_h->vy*h, e->plan->n->vz*n + v_l->vz*l + v_h->vz*h);
    
    free_vect(v_h);
    free_vect(v_l);
}

void deplace_ecran_semi_vect(bloc_ecran_t* e, float n){
    vect_t* v = sp_vect(e->plan->n->vx, e->plan->n->vy, 0);
    normalise_vect(v);
    deplace_ecran(e, v->vx*n, v->vy*n, v->vz*n);
    free_vect(v);
}

void rotation_largeur_ecran(bloc_ecran_t*e, float teta_rd){
    normalise_vect(e->plan->n);
    double phi2 = asin(e->plan->n->vz);
    e->plan->n->vz = 0;
    normalise_vect(e->plan->n);
    double phi = acos(e->plan->n->vx);
    if (e->plan->n->vy<0){phi = -phi;}
    phi += teta_rd;
    vect_t* new_v = sp_vect(cosf(phi2)*cosf(phi), cosf(phi2)*sinf(phi), sinf(phi2));
    normalise_vect(new_v);
    free_vect(e->plan->n);
    e->plan->n = new_v;
    free_pt(e->plan->A);
    e->plan->A = sp_pt(e->A->x + new_v->vx*e->d, e->A->y + new_v->vy*e->d, e->A->z + new_v->vz*e->d);
}

void rotation_hauteur_ecran(bloc_ecran_t*e, float teta_rd){
    normalise_vect(e->plan->n);
    double phi = asin(e->plan->n->vz);
    if (phi + teta_rd > 1.5) {
        phi = 1.5;
    } else if (phi + teta_rd < -1.5){
        phi = -1.5;
    } else {
        phi += teta_rd;
    } 
    e->plan->n->vz = 0;
    normalise_vect(e->plan->n);
    double phi2 = acos(e->plan->n->vx);
    if (e->plan->n->vy<0){phi2 = -phi2;}
    vect_t* new_v = sp_vect(cosf(phi)*cosf(phi2), cosf(phi)*sinf(phi2), sinf(phi));
    normalise_vect(new_v);
    free_vect(e->plan->n);
    e->plan->n = new_v;
    free_pt(e->plan->A);
    e->plan->A = sp_pt(e->A->x + new_v->vx*e->d, e->A->y + new_v->vy*e->d, e->A->z + new_v->vz*e->d);
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
    for (int i = 0; i < s->n_sph; i++){
        free_obj_shp(s->list_sph[i]);
    }
    for (int i = 0; i <s->n_plan;i++){
        free_obj_plan(s->list_plan[i]);
    }
    free(s->list_sph);
    free(s);
}
