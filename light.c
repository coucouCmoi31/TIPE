#include "light.h"

float point_lum_sph(pt_t* point, sph_t* sphe, ch_lum_t* lums, pt_t* camera){
    pt_t* source = lums->tete->light->position;
    float distance = normale(vect_from_points(point, source));
    float watt_r = lums->tete->light->intensité * (1/(distance*distance));
    float watt_eff = watt_r * pro_scal(vect_from_points(point, &source),norm_sph(sphe, point));
    return watt_eff;
}