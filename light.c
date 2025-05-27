#include "light.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
    
float point_lum_sph(pt_t* point, sph_t* sphe, ch_lum_t* lums, pt_t* camera){
    pt_t* source = lums->tete->light->position;
    vect_t* v = vect_from_points(point, source);
    float distance = normale(v);
    float watt_r = lums->tete->light->intensité; // / (distance*distance);
    vect_t* n = norm_sph(sphe, point);
    float watt_eff = watt_r * pro_scal(v, n);

    //FILE* f = fopen("out_lumi.txt", "a");
    //fprintf(f, "-%f-", watt_eff);
    //fclose(f);

    free_vect(v);
    free_vect(n);
    return watt_eff;
}

HSL_t RGB_to_HSL(SDL_Color col){
    float R1 = col.r/255;
    float G1 = col.g/255;
    float B1 = col.b/255;
    float Cmax = maxc(R1, G1, B1);
    float Cmin = minc(R1, G1, B1);
    float del = Cmax-Cmin;
    float L1=(Cmax - Cmin)/2;
    float H1;
    float S1;
    if (del =  0) {
        H1=0;
        S1=0;
    } else {
        S1=del/(1-abs(2L-1));
    }
    if (R1 >= ((G1+B1)/2 + abs(G1-B1))){
        H1=60*(((G1-B1)/del)/6);
    } else if (G1 >= ((R1+B1)/2 + abs(R1-B1))){
        H1=60*(((B1-R1)/del)+2);
    } else {
        H1=60*(((R1-G1)/del)+4);
    }
    HSL_t couleur_HSL;
    couleur_HSL.H = H1;
    couleur_HSL.S = S1;
    couleur_HSL.L = L1;
    return couleur_HSL;
}

SDL_Color HSL_to_RGB(HSL_t col){
    float C = (1 - abs(2*col.L - 1))*col.S;
    float H1s = col.H / 60;
    int temp = H1s/2;
    float X = C * (1 - abs((H1s - 2*temp) - 1));
    float m = col.L - C/2;
    float R1;
    float G1;
    float B1;
    if (col.H < 60) {
        R1 = C;
        G1 = X;
        B1 = 0;
    }else if (col.H < 120) {
        R1 = X;
        G1 = C;
        B1 = 0;
    }else if (col.H < 180) {
        R1 = 0;
        G1 = C;
        B1 = X;
    }else if (col.H < 240) {
        R1 = 0;
        G1 = X;
        B1 = C;
    }else if (col.H < 300) {
        R1 = X;
        G1 = 0;
        B1 = C;
    }else if (col.H < 360) {
        R1 = C;
        G1 = 0;
        B1 = X;
    }
    SDL_Color sortie;
    sortie.r=(R1 + m)*255;
    sortie.g=(G1 + m)*255;
    sortie.b=(B1 + m)*255;
    sortie.a = 255;
    return sortie;    
}


float point_lum_pl(pt_t* point, plan_i* pl, ch_lum_t* lums, pt_t* camera, sph_t** spheres, int nb_sphe){
    pt_t* a_supp = malloc(sizeof(pt_t));
    pt_t* source = lums->tete->light->position;
    vect_t* v = vect_from_points(point, source);
    float distance = normale(v);
    float watt_r = lums->tete->light->intensité; // / (distance*distance);
    float watt_eff = watt_r * pro_scal(v, pl->n);
    for (int i = 0; i < nb_sphe; i++){
        if cr_vect_sphere(point, v, spheres[i],a_supp) {
            watt_eff = watt_eff/2;
        }
    } 
    free_vect(v);
    return watt_eff;
}

