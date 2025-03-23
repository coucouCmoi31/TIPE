#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "affichage.h"

int MART_SetPixel(SDL_Renderer* renderer, int cx, int cy, SDL_Color color){
    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(renderer, cx, cy);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}



