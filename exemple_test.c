#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "objets_maths.h"
#include "light.h"

/*test avec juste une sphère et une source de lumière*/
int test_v1(){
    ch_lum_t* leslumi = malloc(sizeof(ch_lum_t));
    leslumi->tete = malloc(sizeof(mai_lum_t));
    leslumi->tete->suivant = NULL;
    leslumi->tete->light = malloc(sizeof(lum_t));
    leslumi->tete->light->intensité = 1.0;
    leslumi->tete->light->position = malloc(sizeof(pt_t));
    leslumi->tete->light->position->x = 1200.0;
    leslumi->tete->light->position->y = 0.0;
    leslumi->tete->light->position->z = 1600.0;

    

    return 0;
}