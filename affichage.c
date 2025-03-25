#include <stdbool.h>

#include <SDL2/SDL.h>
#include "affichage.h"
#include "objets_graphique.h"
#include "objets_maths.h"

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
    return 0;
}

int Mart_ColorSphere(SDL_Renderer* renderer, obj_sph_t* sph, bloc_ecran_t* e){
    /*
    int h = e->hp * 2;
    int l = e->lp * 2;
    pt_t* temp;
    plan_i* pl = e->plan;
    vect_t* v = pl->n;
    
    cr_vect_plan(e->A, , e->plan, temp);
    for (int i = 0; i < h; i++){
        for(int j = 0; i < j; j++){
            
    }
    }
    */
    return 0;
}
