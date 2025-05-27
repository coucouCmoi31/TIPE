#ifndef obj_m
#define obj_m = 10

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

/*toutes les structures sont dans le tas*/
struct point{
    float x;
    float y;
    float z;
};
typedef struct point pt_t;

struct vect{
    float vx;
    float vy;
    float vz;
};
typedef struct vect vect_t;

struct planinf{
    pt_t* A;
    vect_t* n;
};
typedef struct planinf plan_i;

struct sphere{
    pt_t* centre;
    float rayon;
};
typedef struct sphere sph_t;

// struct demi_droite;
// typedef struct demi_droite dd_t;
// fonctions min et max sur 3 int, et val absolue de float
int maxc(int a, int b, int c);
int minc(int a, int b, int c);


/*crée un point de coordonées (a,b,c)*/
pt_t* sp_pt(float a, float b, float c);

/*crée un vecteur de coordonées (x,y,z)*/
vect_t* sp_vect(float x, float y, float z);

/*crée un plan infini de vecteur normal C (n) et passant par le point B (A)*/
plan_i* sp_plan(vect_t* C, pt_t* B);

/*crée et renvoie en sphere de rayon R et de centre le point O*/
sph_t* sp_sph(float r, pt_t* O);

/*free l'élement appelé (et ses constructeurs)*/
void free_pt(pt_t* A);

void free_vect(vect_t* A);

void free_plan(plan_i* B);

void free_sph(sph_t* A);

/*crée un vecteur à partir de deux points D départ, A arrivée*/
vect_t* vect_from_points(pt_t* D, pt_t* A);

/*renvoie le point où la droite formée de dep et direc et le plan se croisent, modifiant la valeur de sortie*/
/*renvoie 1: à fonctionné; 0: le point est derrière la droite*/
int cr_vect_plan(pt_t* dep, vect_t* direc, plan_i* plan, pt_t* sortie);

/*renvoie le point où la droite formée de dep et direc et la sphère se croisent, modifiant la valeur de sortie*/
/*renvoie 1: à fonctionné; 0: le point est derrière la droite ou on est dans la sphère*/
int cr_vect_sphere(pt_t* dep, vect_t* direc, sph_t* sphe, pt_t* sortie);

/*Renvoie la normale d'un vecteur*/
float normale(vect_t* v);

/*renvoie le produit scalaire de deux vecteurs*/
float pro_scal(vect_t* a, vect_t* b);

/*renvoie le vecteur normal d'une sphère en un point de contact (le vecteur normal est unitaire)*/
vect_t* norm_sph(sph_t* sph, pt_t* contact);

/* calcule le vectaur largeur par rapport a normal en le met dans res */
int cr_vect_l(vect_t* normal, vect_t* res);

/* calcule le vectaur hauteur par rapport a normal en le met dans res */
int cr_vect_h(vect_t* normal, vect_t* res);

/* normalize le vercteur à 1 */
int normalise_vect(vect_t* v);

/* deplace p de v */
int deplace_pt(pt_t* p, vect_t* v);

/* copy un pt */
int copy_pt(pt_t* src, pt_t* dst);

/*  */
int min_distance(pt_t* origine, pt_t* pt1, pt_t* pt2);

#endif