#include "fen.h"
#include "objets_graphique.h"
#include "objets_maths.h"
#include "affichage.h"

int main (){
    SDL_Window* fen = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = NULL;
    SDL_Event events;
    int statut = EXIT_FAILURE;
    int size_fen[2] = {500, 500};
    
    /* ---------------------- init ----------------------*/
    if (0 != MART_init(&fen, &renderer, size_fen[0], size_fen[1])){
        goto Quit;
    }
    /* --------------------------------------------------*/

    SDL_Color rouge = {255, 0, 0, 255};
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Color vert = {0, 255, 0, 255};
    SDL_Color noir = {0, 0, 0, 255};

    pt_t* A = sp_pt(0, 0, 0);
    pt_t* B = sp_pt(500, 0, 0);
    bloc_ecran_t* e = sp_ecran(A, B, 500, 500);
    obj_sph_t* sphere = sp_obj_sph(sp_sph(500, sp_pt(1000, 0, 0)), rouge);

    MART_SetColorWindow(renderer, blanc);

    while(events.type != SDL_KEYUP && events.type != SDL_QUIT){
        SDL_PollEvent( &events );
    }

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