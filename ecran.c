#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

#include "ecran.h"
#include "objets_maths.h"

struct bloc_ecran{
    pt_t* A;
    plan_i* plan;
    int hp; /*la demi hauteur en px*/
    int lp; /*la demi largueur en px*/
};

bloc_ecran_t* sp_ecran(pt_t* A, pt_t* B, int fen_px_h, int fen_px_l){
    bloc_ecran_t* e = malloc(sizeof(bloc_ecran_t));
    e->A = A;
    e->hp = fen_px_h/2;
    e->lp = fen_px_l/2;
    e->plan = sp_plan(vect_from_points(A, B), B);
    return e;
}

void free_bloc_ecran(bloc_ecran_t* e){
    free_plan(e->plan);
    free_pt(e->A);
    free(e);
}
