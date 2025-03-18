#ifndef obj_m
#define obj_m = 10

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


/*toutes les structures sont dans le tas*/
struct point;
typedef struct point pt_t;

struct vect;
typedef struct vect vect_t;

struct vect_cyl;
typedef struct vect vect_cyl_t;

struct planinf;
typedef struct planinf plan_i;

struct sphere;
typedef struct sphere sph_t;

/*crée un point de coordonées (a,b,c)*/
pt_t* sp_pt(float a, float b, float c);

/*crée un vecteur de coordonées (x,y,z)*/
vect_t* sp_vect(float x, float y, float z);

/*crée un plan infini de vecteur normal C (n) et passant par le point B (A)*/
plan_i* sp_plan(vect_t* C, pt_t* B);

/*crée et renvoie en sphere de rayon R et de centre le point O*/
sph_t* sp_sph(float r, pt_t* O);

/*crée un vecteur en coo cylindrique en fonction du vecteur v */
vect_cyl_t* sp_vect_cyl(vect_t* v);

/*free l'élement appelé (et ses constructeurs)*/
void free_pt(pt_t* A);

void free_vect(vect_t* A);

void free_plan(plan_i* B);

void free_sph(sph_t* A);

void free_vect_cyl(vect_cyl_t* v);

/*crée un vecteur à partir de deux points D départ, A arrivée*/
vect_t* vect_from_points(pt_t* D, pt_t* A);

#endif
