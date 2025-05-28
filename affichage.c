#include <stdbool.h>

#include <SDL2/SDL.h>
#include "affichage.h"
#include "objets_graphique.h"
#include "objets_maths.h"
#include <stdio.h>
#include <stdlib.h>
#include "light.h"

int MART_SetPixel(SDL_Renderer* renderer, int cx, int cy, SDL_Color color){
    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(renderer, cx, cy);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    return 0;
}

int MART_ColorSphereOnePixel(SDL_Renderer* renderer, int cx, int cy, obj_sph_t* sphere, pt_t* origine, vect_t* direction, ch_lum_t* leslumi){
    pt_t* sortie = sp_pt(0, 0, 0);
    if (cr_vect_sphere(origine, direction, sphere->sph, sortie) == 1){
        // float taux = point_lum_sph(sortie, sphere->sph, leslumi, origine);
        MART_SetPixel(renderer, cx, cy, sphere->c);
    }
    /*
    else {
        printf("elle est deriere \n");
    }
    */
    free_pt(sortie);
    return 0;
}

int Mart_ColorPlanOnePixiel(SDL_Renderer* renderer, int cx, int cy, obj_plan_i* plan, pt_t* origine, vect_t* direction){
    pt_t* sortie = sp_pt(0, 0, 0);
    if (cr_vect_plan(origine, direction, plan->plan, sortie) == 1){
        MART_SetPixel(renderer, cx, cy, plan->c);
    }
    /*
    else {
        printf("elle est deriere \n");
    }
    */
    free_pt(sortie);
    return 0;
}

int Mart_ColorSphere(SDL_Renderer* renderer, obj_sph_t* sph, bloc_ecran_t* e, ch_lum_t* leslumi){
    int h = e->hp * 2;
    int l = e->lp * 2;
    vect_t* v_l = sp_vect(0, 0, 0);
    cr_vect_l(e->plan->n, v_l);
    normalise_vect(v_l);
    vect_t* v_h = sp_vect(0, 0, 0);
    cr_vect_h(e->plan->n, v_h);
    normalise_vect(v_h);
    pt_t* D = sp_pt(e->plan->A->x - v_h->vx*e->hp - v_l->vx*e->lp , e->plan->A->y - v_h->vy*e->hp - v_l->vy*e->lp, e->plan->A->z - v_h->vz*e->hp - v_l->vz*e->lp);
    pt_t* C = sp_pt(0, 0, 0);
    for (int i = 0; i < h; i++){
        copy_pt(D, C);
        for(int j = 0; j < l; j++){
            vect_t* vect = vect_from_points(e->A, C);
            MART_ColorSphereOnePixel(renderer, j, i, sph, e->A, vect, leslumi);
            free_vect(vect);
            deplace_pt(C, v_l);
            /*printf("%d x %d\n", j, i);*/
        }
        deplace_pt(D, v_h);
    }
    free_vect(v_h);
    free_vect(v_l);
    free_pt(D);
    free_pt(C);
    return 0;
}

int Mart_ColorPlan(SDL_Renderer* renderer, obj_plan_i* pl, bloc_ecran_t* e){
    int h = e->hp * 2;
    int l = e->lp * 2;
    vect_t* v_l = sp_vect(0, 0, 0);
    cr_vect_l(e->plan->n, v_l);
    normalise_vect(v_l);
    vect_t* v_h = sp_vect(0, 0, 0);
    cr_vect_h(e->plan->n, v_h);
    normalise_vect(v_h);
    pt_t* D = sp_pt(e->plan->A->x - v_h->vx*e->hp - v_l->vx*e->lp , e->plan->A->y - v_h->vy*e->hp - v_l->vy*e->lp, e->plan->A->z - v_h->vz*e->hp - v_l->vz*e->lp);
    pt_t* C = sp_pt(0, 0, 0);
    for (int i = 0; i < h; i++){
        copy_pt(D, C);
        for(int j = 0; j < l; j++){
            vect_t* vect = vect_from_points(e->A, C);
            Mart_ColorPlanOnePixiel(renderer, j, i, pl, e->A, vect);
            free_vect(vect);
            deplace_pt(C, v_l);
            /*printf("%d x %d\n", j, i);*/
        }
        deplace_pt(D, v_h);
    }
    free_vect(v_h);
    free_vect(v_l);
    free_pt(D);
    free_pt(C);
    return 0;
}

int MART_ColorSpiritOnePixel(SDL_Renderer* renderer, int cx, int cy, spirit_t* spirit, pt_t* origine, vect_t* direction, ch_lum_t* leslumi){
    pt_t* sortie = sp_pt(0, 0, 0);
    pt_t* min_sortie = sp_pt(0, 0, 0);
    int indice = -1;
    int type = 0;
    for (int i = 0; i<spirit->n_sph;i++){
        if (cr_vect_sphere(origine, direction, spirit->list_sph[i]->sph, sortie) == 1){
            if (indice == -1 || min_distance(origine, sortie, min_sortie) == 1){
                copy_pt(sortie, min_sortie);
                indice = i;
                type = 1;
            }
        }
    }
    for (int i = 0; i<spirit->n_plan;i++){
        if (cr_vect_plan(origine, direction, spirit->list_plan[i]->plan, sortie) == 1){
            if (indice == -1 || min_distance(origine, sortie, min_sortie) == 1){
                copy_pt(sortie, min_sortie);
                indice = i;
                type = 2;
            }
        }
    }
    // printf("i -> %d \n", indice);
    if (type == 1) {
        float eff = point_lum_sph(min_sortie, spirit->list_sph[indice]->sph, leslumi, origine);
        HSL_t temp = RGB_to_HSL(spirit->list_sph[indice]->c);
        temp.L *= eff;
        MART_SetPixel(renderer, cx, cy, HSL_to_RGB(temp));
    } else if (type == 2){
        float eff = point_lum_pl(min_sortie, spirit->list_plan[indice]->plan, leslumi, origine, spirit->list_sph, spirit->n_sph);
        HSL_t temp = RGB_to_HSL(spirit->list_plan[indice]->c);
        temp.L *= eff;
        MART_SetPixel(renderer, cx, cy, HSL_to_RGB(temp));
    }
    free_pt(min_sortie);
    free_pt(sortie);
    return 0;
}

int MART_ColorSpirit(SDL_Renderer* renderer, spirit_t* spirit, bloc_ecran_t* e, ch_lum_t* leslumi){
    int h = e->hp * 2;
    int l = e->lp * 2;
    vect_t* v_l = sp_vect(0, 0, 0);
    cr_vect_l(e->plan->n, v_l);
    normalise_vect(v_l);
    vect_t* v_h = sp_vect(0, 0, 0);
    cr_vect_h(e->plan->n, v_h);
    normalise_vect(v_h);
    pt_t* D = sp_pt(e->plan->A->x - v_h->vx*e->hp - v_l->vx*e->lp , e->plan->A->y - v_h->vy*e->hp - v_l->vy*e->lp, e->plan->A->z - v_h->vz*e->hp - v_l->vz*e->lp);
    pt_t* C = sp_pt(0, 0, 0);
    for (int i = 0; i < h; i++){
        copy_pt(D, C);
        for(int j = 0; j < l; j++){
            vect_t* vect = vect_from_points(e->A, C);
            MART_ColorSpiritOnePixel(renderer, j, i, spirit, e->A, vect, leslumi);
            free_vect(vect);
            deplace_pt(C, v_l);
            /*printf("%d x %d\n", j, i);*/
        }
        deplace_pt(D, v_h);
    }
    free_vect(v_h);
    free_vect(v_l);
    free_pt(D);
    free_pt(C);
}

