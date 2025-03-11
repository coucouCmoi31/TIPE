#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "objets_maths.h"

void tests(){
    pt_t* pointA = sp_pt(1.0, 2.0, 3.0);

    vect_t* vecteurB = sp_vect(0.0, -1.0, 1.0);

    plan_i* planC = sp_plan(vecteurB, pointA);

    sph_t* bouleD = sp_sph(5, pointA);

    free_plan(planC);

    free_sph(bouleD);

}

int main(){
    tests();

    return 0;
}