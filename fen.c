#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fen.h"

int MART_init(SDL_Window **window, SDL_Renderer **renderer, int w, int h){
    if (0 != SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_SHOWN, window, renderer)){
        printf("Erreur SDL_CreateWindowAndRenderer : %s \n", SDL_GetError());
        return -1;
    }
    SDL_SetRenderDrawBlendMode(*renderer, SDL_BLENDMODE_BLEND);

    SDL_SetWindowTitle(*window, "MART");
    return 0;
}

int MART_SetColorWindow(SDL_Renderer* renderer, SDL_Color color){
    if (0 != SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a)){
        return -1;
    }
    if (0 != SDL_RenderClear(renderer)){
        return -1;
    } return 0;
}

