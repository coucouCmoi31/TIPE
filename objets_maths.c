#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>

#include "objets_maths.h"

float maxc(float a, float b, float c){
    if (a >= b) {
        if (a >= c) {
            return a;
        } else {
            return c;
        }
    } else {
        if (b >= c) {
            return b;
        } else {
            return c;
        }
    }
}

float minc(float a, float b, float c){
    if (a >= b) {
        if (c >= b) {
            return b;
        } else {
            return c;
        }
    } else {
        if (a >= c) {
            return c;
        } else {
            return a;
        }
    }
}

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

vect_t* vect_from_points(pt_t* D, pt_t* A){
    vect_t* V = malloc(sizeof(vect_t));
    V->vx = A->x - D->x;
    V->vy = A->y - D->y;
    V->vz = A->z - D->z;
    return V;
}

int cr_vect_plan(pt_t* dep, vect_t* direc, plan_i* plan, pt_t* sortie){
    float t = (plan->n->vx * (plan->A->x - dep->x) + plan->n->vy * (plan->A->y - dep->y) + plan->n->vz * (plan->A->z - dep->z))/(plan->n->vx * direc->vx + plan->n->vy * direc->vy + plan->n->vz * direc->vz);
    if (t <= 0){
        return 0;
    }
    else{
        sortie->x = dep->x + t * direc->vx;
        sortie->y = dep->y + t * direc->vy;
        sortie->z = dep->z + t * direc->vz;
        return 1;
    }
}

int cr_vect_sphere(pt_t* dep, vect_t* direc, sph_t* sphe, pt_t* sortie){
    float a = powf(direc->vx, 2.0) + powf(direc->vy, 2.0) + powf(direc->vz, 2.0);
    float b = 2*(direc->vx * (dep->x - sphe->centre->x) + direc->vy * (dep->y - sphe->centre->y) + direc->vz * (dep->z - sphe->centre->z));
    float c = powf((dep->x - sphe->centre->x), 2.0) + powf((dep->y - sphe->centre->y),2.0) + powf((dep->z - sphe->centre->z),2.0) - powf(sphe->rayon, 2.0);
    float delta = powf(b, 2.0) - 4*a*c;
    if (delta <= 0.0){
        return 0;
    }
    float racine = (-b - sqrtf(delta))/(2*a);
    if (racine <= 0.0){
        sortie->x = dep->x + racine * direc->vx ;
        sortie->y = dep->y + racine * direc->vy ;
        sortie->z = dep->z + racine * direc->vz ;
        return 1;
    }
    else{
        sortie->x = dep->x + racine * direc->vx ;
        sortie->y = dep->y + racine * direc->vy ;
        sortie->z = dep->z + racine * direc->vz ;
        return 1;
    }
}

float normale(vect_t* v){
    return sqrtf(v->vx*v->vx + v->vy*v->vy + v->vz*v->vz);
}

float pro_scal(vect_t* a, vect_t* b){
    return ((a->vx*a->vx)+(a->vy*a->vy)+(a->vz*a->vz)+(b->vx*b->vx)+(b->vy*b->vy)+(b->vz*b->vz)-((a->vx-b->vx)*(a->vx-b->vx)+(a->vy-b->vy)*(a->vy-b->vy)+(a->vz-b->vz)*(a->vz-b->vz)))/2;
}

vect_t* norm_sph(sph_t* sph, pt_t* contact){
    vect_t* sortie = vect_from_points(sph->centre, contact);
    assert( 1 == normalise_vect(sortie));
    return sortie;
}

int cr_vect_l(vect_t* normal, vect_t* res){
    res->vx = normal->vy;
    res->vy = - normal->vx;
    res->vz = 0;
    return 1;    
}

int cr_vect_h(vect_t* normal, vect_t* res){
    vect_t* v_l = sp_vect(0, 0, 0);
    cr_vect_l(normal, v_l);
    normalise_vect(v_l);
    res->vx = - v_l->vy * normal->vz;
    res->vy = v_l->vx * normal->vz;
    res->vz = -fabsf(v_l->vx*normal->vy - v_l->vy*normal->vx); 
    free_vect(v_l);
    return 1;
}

int normalise_vect(vect_t* v){
    float n = sqrtf(v->vx*v->vx + v->vy*v->vy + v->vz*v->vz);
    v->vx /= n;
    v->vy /= n;
    v->vz /= n;
    return 1;
}

int deplace_pt(pt_t* p, vect_t* v){
    p->x += v->vx;
    p->y += v->vy;
    p->z += v->vz;
    return 1;
}

int copy_pt(pt_t* src, pt_t* dst){
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
    return 1;
}

int min_distance(pt_t* origine, pt_t* pt1, pt_t* pt2){
    double d1 = (origine->x-pt1->x)*(origine->x-pt1->x) + (origine->y-pt1->y)*(origine->y-pt1->y) + (origine->z-pt1->z)*(origine->z-pt1->z);
    double d2 = (origine->x-pt2->x)*(origine->x-pt2->x) + (origine->y-pt2->y)*(origine->y-pt2->y) + (origine->z-pt2->z)*(origine->z-pt2->z);
    if (d1 < d2) {
        return 1;
    } else {
        return 2;
    }
}
