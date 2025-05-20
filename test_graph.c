#include "fen.h"
#include "objets_graphique.h"
#include "objets_maths.h"
#include "affichage.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "light.h"

void print(SDL_Renderer* renderer, TTF_Font* police, char* txt, int cx, int cy, SDL_Color c){
    SDL_Surface* surface = TTF_RenderText_Solid(police, txt, c);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect r = {cx, cy, cx+surface->w/2, cy+surface->h/2};
    SDL_RenderCopy(renderer, texture, NULL, &r);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
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
    SDL_Color bleu_ciel = {86, 207, 248, 255};

    TTF_Font *police = TTF_OpenFont("police.ttf", 50);
    if (police == NULL){
        printf("erreur chargement police : %s \n", TTF_GetError());
        goto Quit;
    }

    pt_t* A = sp_pt(0, 0, 800);
    pt_t* B = sp_pt(500, 0, 800);
    bloc_ecran_t* e = sp_ecran(A, B, 500, 500);
    spirit_t* spirit = sp_spirit_vide();
    ajouter_shp_spirit(spirit, sp_obj_sph(sp_sph(500, sp_pt(1500, 0, 800)), rouge));
    ajouter_shp_spirit(spirit, sp_obj_sph(sp_sph(500, sp_pt(2000, 1000, 800)), noir));
    obj_plan_i* pl = sp_obj_plan(sp_plan(sp_vect(0, 0, 1), sp_pt(0, 0, 0)), vert);

    ch_lum_t* leslumi;
    leslumi = malloc(sizeof(ch_lum_t));
    leslumi->tete = malloc(sizeof(mai_lum_t));
    leslumi->tete->suivant = NULL;
    leslumi->tete->light = malloc(sizeof(lum_t));
    leslumi->tete->light->intensité = 5000;
    leslumi->tete->light->position = malloc(sizeof(pt_t));
    leslumi->tete->light->position->x = 1200.0;
    leslumi->tete->light->position->y = 0.0;
    leslumi->tete->light->position->z = 10000.0;

    MART_SetColorWindow(renderer, bleu_ciel);
    Mart_ColorPlan(renderer, pl, e);
    MART_ColorSpirit(renderer, spirit, e);

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
                if (events.key.keysym.sym == SDLK_ESCAPE){
                    prog = false;
                } else if (events.key.keysym.sym == SDLK_UP){
                    deplace_ecran_semi_vect(e, 100);
                } else if (events.key.keysym.sym == SDLK_DOWN){
                    deplace_ecran_semi_vect(e, -100);
                } else if (events.key.keysym.sym == SDLK_RIGHT){
                    deplace_ecran_vect(e, 0, 100, 0);
                } else if (events.key.keysym.sym == SDLK_LEFT){
                    deplace_ecran_vect(e, 0, -100, 0);
                } else if (events.key.keysym.sym == SDLK_z){
                    rotation_hauteur_ecran(e, 0.1);
                } else if (events.key.keysym.sym == SDLK_s){
                    rotation_hauteur_ecran(e, -0.1);
                } else if (events.key.keysym.sym == SDLK_q){
                    rotation_largeur_ecran(e, 0.2);
                } else if (events.key.keysym.sym == SDLK_d){
                    rotation_largeur_ecran(e, -0.2);
                } else if (events.key.keysym.sym == SDLK_LCTRL){
                    deplace_ecran_vect(e, 0, 0, 100);
                } else if (events.key.keysym.sym == SDLK_SPACE){
                    deplace_ecran_vect(e, 0, 0, -100);
                }
            }
        }
        MART_SetColorWindow(renderer, bleu_ciel);

        Mart_ColorPlan(renderer, pl, e);
        MART_ColorSpirit(renderer, spirit, e);

        sprintf(aff, "fps : %d", fps);
        print(renderer, police, aff, 10, 10, noir);
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
    free_all_spirit(spirit);
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
