#ifndef fen_guard
#define fen_guard

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int MART_init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);

int MART_SetColorWindow(SDL_Renderer* renderer, SDL_Color color);

#endif
