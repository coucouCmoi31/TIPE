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
    float d;
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
    int max_spirit_sph;
    int n_sph;
    obj_sph_t** list_sph;
    int max_spirit_plan;
    int n_plan;
    obj_plan_i** list_plan;
};
typedef struct spirit spirit_t;

/* free les elements et leur constructeur */
void free_obj_shp(obj_sph_t* sphere);

void free_bloc_ecran(bloc_ecran_t* e);

void free_obj_plan(obj_plan_i* p);

void free_all_spirit(spirit_t* s);


/*cree un bloc pour l'ecran d'origine A en de plan de centre B de dimention h et l en px*/
bloc_ecran_t* sp_ecran(pt_t* A, pt_t* B, int fen_px_h, int fen_px_l);

/* cree un objet sphere en lui atribuant la couleur c */
obj_sph_t* sp_obj_sph(sph_t* sph, SDL_Color c);

/* cree un objet plan en lui atribuant la couleur c */
obj_plan_i* sp_obj_plan(plan_i* plan, SDL_Color c);

/* cree un ensemble vide de spirite */
spirit_t* sp_spirit_vide();

/* augmente la taille en memoire de s */
void agrandie_taille_max_spirit(spirit_t* s);

/* ajoute sph dans s */
void ajouter_shp_spirit(spirit_t* s, obj_sph_t* sph);
void ajouter_plan_spirit(spirit_t* s, obj_plan_i* plan);

/* deplace e selon  (dx, dy, dz) */
void deplace_ecran(bloc_ecran_t* e, float dx, float dy, float dz);

/* deplace e selon vect normal n, vect largeur l, vect hauteur h */
void deplace_ecran_vect(bloc_ecran_t* e, float n, float l, float h);

/* deplace e selon vect n */
void deplace_ecran_semi_vect(bloc_ecran_t* e, float n);

/* tourne l'écran dans la largeur selon teta_rd */
void rotation_largeur_ecran(bloc_ecran_t*e, float teta_rd);

/* tourne l'écran dans la hauteur selon teta_rd */
void rotation_hauteur_ecran(bloc_ecran_t*e, float teta_rd);

#endif
