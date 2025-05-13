#include "light.h"
#include <stdio.h>
#include <stdlib.h>

float point_lum_sph(pt_t* point, sph_t* sphe, ch_lum_t* lums, pt_t* camera){
    pt_t* source = lums->tete->light->position;
    vect_t* v = vect_from_points(point, source);
    float distance = normale(v);
    float watt_r = lums->tete->light->intensité * (1/(distance*distance));
    vect_t* n = norm_sph(sphe, point);
    float watt_eff = 255 * watt_r * pro_scal(v, n);

    //FILE* f = fopen("out_lumi.txt", "a");
    //fprintf(f, "-%f-", watt_eff);
    //fclose(f);
    free_vect(v);
    free_vect(n);
    return watt_eff;
}

HSL_t* RGB_to_HSL(SDL_color* col){
    float R1 = col->r/255;
    float G1 = col->g/255;
    float B1 = col->b/255;
    float Cmax = maxc(R1, G1, B1);
    float Cmin = minc(R1, G1, B1);
    float del = Cmax-Cmin;
    float H1;
    float S1;
    if del =  0 {
        H1=0;
        S1=0;
    } else {
        S1=del/(1-abs(2L-1));
    }
    if (R1 >= ((G1+B1)/2 + abs(G1-B1))){
        H1=60*(((G1-B1)/del)%6);
    } else if (G1 >= ((R1+B1)/2 + abs(R1-B1))){
        H1=60*(((B1-R1)/del)+2);
    } else {
        H1=60*(((R1-G1)/del)+4);
    }
    L1=(Cmax - Cmin)/2;
    HSL_t* couleur_HSL = malloc(sizeof(HSL_t));
    couleur_HSL->H = H1;
    couleur_HSL->S = S1;
    couleur_HSL->L = L1;
    return couleur_HSL;
}
