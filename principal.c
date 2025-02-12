#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int SetColorWindow(SDL_Renderer* renderer, SDL_Color color){
    if (0 != SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255)){
        return -1;
    }
    if (0 != SDL_RenderClear(renderer)){
        return -1;
    } return 0;
}

int main (){
    SDL_Window* fen = NULL;
    SDL_Renderer* renderer = NULL;
    int statut = EXIT_FAILURE;
    int size_fen[2] = {500, 500};

    /* ---------------------- init ----------------------*/
    if (0 != SDL_Init(SDL_INIT_VIDEO)){
        printf("Erreur SDL_Init : %s \n", SDL_GetError());
        goto Quit;
    }
    fen = SDL_CreateWindow("Ma fenetre", 50, 50, size_fen[0], size_fen[1], SDL_WINDOW_SHOWN);
    if (fen == NULL){
        printf("Erreur SDL_CreateWindow : %s \n", SDL_GetError());
        goto Quit;
    }
    renderer = SDL_CreateRenderer(fen, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL){
        printf("Erreur SDL_CreateRenderer : %s \n", SDL_GetError());
        renderer = SDL_CreateRenderer(fen, -1, SDL_RENDERER_SOFTWARE);
        if (renderer == NULL){
            printf("Erreur SDL_CreateRenderer : %s \n", SDL_GetError());
            goto Quit;
        }
    }
    /* --------------------------------------------------*/

    SDL_Color rouge = {255, 0, 0, 255};
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Color noir = {0, 0, 0, 255};
    

    SDL_Delay(1000);
    
    SetColorWindow(renderer, blanc);
    SDL_RenderPresent(renderer);


    /*
    SDL_Point pt [640];
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < 640; i++){
        pt[i].x = 100 + i; 
        pt[i].y = 100;
    }
    SDL_RenderDrawPoints(renderer, pt, 640);
    SDL_RenderPresent(renderer);

    
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(renderer, 100, 100, 740, 300);
    SDL_RenderPresent(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect rec = {100, 100, 100, 100};
    SDL_RenderFillRect(renderer, &rec);
    SDL_RenderPresent(renderer);
    */

    SDL_SetRenderDrawColor(renderer, noir.r, noir.g, noir.b, noir.a);
    SDL_Rect rec = {0, 0, (size_fen[0])/8, (size_fen[1])/8};
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if ((i+j) % 2 == 0){
                rec.x = rec.h * i;
                rec.y = rec.h * j;
                SDL_RenderFillRect(renderer, &rec);
            }
        }
    }
    
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);


    statut = EXIT_SUCCESS;
Quit:
    if (fen != NULL){
        SDL_DestroyWindow(fen);
    }
    if (renderer != NULL){
        SDL_DestroyRenderer(renderer);
    }
    SDL_Quit();
    return statut;
}
