#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "objets_maths.h"

struct point{
    float x;
    float y;
    float z;
};

struct vect{
    float vx;
    float vy;
    float vz;
};

struct planinf{
    pt_t* A;
    vect_t* n;
};

struct sphere{
    pt_t* centre;
    float rayon;
};

pt_t* sp_pt(float a, float b, float c){
    pt_t* P = malloc(sizeof(pt_t));
    P->x = a;
    P->y = b;
    P->z = c;
    return P;
}

vect_t* sp_vect(float x, float y, float z){
    vect_t* V = malloc(sizeof(vect_t));
    V->vx = x;
    V->vy = y;
    V->vz = z;
    return V;
}

plan_i* sp_plan(vect_t* C, pt_t* B){
    plan_i* Pl = malloc(sizeof(plan_i));
    Pl->A = B;
    Pl->n = C;
    return Pl;
}

sph_t* sp_sph(float r, pt_t* O){
    sph_t* Sp = malloc(sizeof(sph_t));
    Sp->rayon = r;
    Sp->centre = O;
    return Sp;
}

void free_pt(pt_t* A){
    free(A);
}

void free_vect(vect_t* A){
    free(A);
}

void free_plan(plan_i* B){
    free_pt(B->A);
    free_vect(B->n);
    free(B);
}

void free_sph(sph_t* A){
    free_pt(A->centre);
    free(A);
}

