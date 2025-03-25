#include <stdbool.h>

#include <SDL2/SDL.h>
#include "affichage.h"
#include "objets_graphique.h"
#include "objets_maths.h"
#include <stdio.h>
#include <stdlib.h>

int MART_SetPixel(SDL_Renderer* renderer, int cx, int cy, SDL_Color color){
    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(renderer, cx, cy);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    return 0;
}

int MART_ColorSphereOnePixel(SDL_Renderer* renderer, int cx, int cy, obj_sph_t* sphere, pt_t* origine, vect_t* direction){
    pt_t* sortie = sp_pt(0, 0, 0);
    if (cr_vect_sphere(origine, direction, sphere->sph, sortie) == 1){
        MART_SetPixel(renderer, cx, cy, sphere->c);
    }
    else {
        printf("elle est deriere \n");
    }
    return 0;
}

int Mart_ColorSphere(SDL_Renderer* renderer, obj_sph_t* sph, bloc_ecran_t* e){
    int h = e->hp * 2;
    int l = e->lp * 2;
    vect_t* v_l = sp_vect(0, 0, 0);
    cr_vect_l(e->plan->n, v_l);
    vect_t* v_h = sp_vect(0, 0, 0);
    cr_vect_h(e->plan->n, v_h);
    pt_t* D = sp_pt(0, 0, 0);
    pt_t* C = sp_pt(0, 0, 0);
    copy_pt(e->plan->A, D);
    for (int i = 0; i < h; i++){
        copy_pt(D, C);
        for(int j = 0; j < l; j++){
            MART_ColorSphereOnePixel(renderer, j, i, sph, e->A, vect_from_points(e->A, C));
            deplace_pt(C, v_l);
            /*printf("%d x %d\n", j, i);*/
        }
        deplace_pt(D, v_h);
    }
    return 0;
}
