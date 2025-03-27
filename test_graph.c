#include "fen.h"
#include "objets_graphique.h"
#include "objets_maths.h"
#include "affichage.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void print(){
    
}

int main (){
    SDL_Window* fen = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = NULL;
    SDL_Event events;
    int statut = EXIT_FAILURE;
    int size_fen[2] = {500, 500};
    
    /* ---------------------- init ----------------------*/
    if (0 != SDL_Init(SDL_INIT_EVERYTHING)){
        goto Quit;
    }
    if (0 != TTF_Init()){
        goto Quit;
    }
    if (0 != MART_init(&fen, &renderer, size_fen[0], size_fen[1])){
        goto Quit;
    }
    /* --------------------------------------------------*/

    SDL_Color rouge = {255, 0, 0, 255};
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Color vert = {0, 255, 0, 255};
    SDL_Color noir = {0, 0, 0, 255};

    TTF_Font *police = TTF_OpenFont("police.ttf", 50);
    if (police == NULL){
        printf("erreur chargement police : %s \n", TTF_GetError());
        goto Quit;
    }

    pt_t* A = sp_pt(0, 0, 500);
    pt_t* B = sp_pt(1000, 000, 500);
    bloc_ecran_t* e = sp_ecran(A, B, 500, 500);
    obj_sph_t* sphere = sp_obj_sph(sp_sph(100, sp_pt(1000, 0, 500)), rouge);
    obj_plan_i* pl = sp_obj_plan(sp_plan(sp_vect(0, 0, 1), sp_pt(0, 0, 0)), vert);

    MART_SetColorWindow(renderer, blanc);
    Mart_ColorPlan(renderer, pl, e);
    Mart_ColorSphere(renderer, sphere, e);

    char aff[50];
    Uint32 ticks = SDL_GetTicks();
    Uint32 last_tick_prog;
    Uint32 last_tick;
    float fps_prog = 0;
    int fps = 0;
    int i = 0;
    bool prog = true;
    while (prog)
    {   
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
            case SDL_QUIT:
                prog = false;
            case SDL_KEYDOWN:
                if (events.key.keysym.sym == SDLK_SPACE){
                    prog = false;
                }
            }
        }
        MART_SetColorWindow(renderer, blanc);

        Mart_ColorPlan(renderer, pl, e);
        Mart_ColorSphere(renderer, sphere, e);

        sprintf(aff, "fps : %d", fps);
        /*
        print(renderer, police, aff, 10, 10, noir);
        */
        SDL_RenderPresent(renderer);

        last_tick = ticks;
        ticks = SDL_GetTicks();
        fps = 1000.0/(ticks - last_tick);
        fps_prog = 1000.0/(ticks - last_tick_prog);
        if (fps_prog>60){
            SDL_Delay((1000.0*(1/60.0 - 1/fps_prog)));
        }
        last_tick_prog = SDL_GetTicks();
    }

    free_obj_plan(pl);
    free_obj_shp(sphere);
    free_bloc_ecran(e);

    statut = EXIT_SUCCESS;
Quit:
    if (police != NULL){
        TTF_CloseFont(police);
    }
    if (renderer != NULL){
        SDL_DestroyRenderer(renderer);
    }
    if (fen != NULL){
        SDL_DestroyWindow(fen);
    }
    TTF_Quit();
    SDL_Quit();
    return statut;
}
