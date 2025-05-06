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
