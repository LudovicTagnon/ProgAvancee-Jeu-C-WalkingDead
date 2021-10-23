//
// Created by ludovic on 24/09/2021.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>


#include "fonctions_SDL.h"



#ifndef V1_CONSTANTS_H
#define V1_CONSTANTS_H

#define SCREEN_WIDTH 1920

#define SCREEN_HEIGHT 1080

#define GRASS_WIDTH  1440

#define GRASS_HEIGHT 800

#define RICK_STEP 50

#define ZOMBIE_STEP 1

#define RICK_WIDTH 138

#define RICK_HEIGHT 248

#define LIFE_SIZE 32

#define TERRAIN_SIZE 100

#define NUMBER_ZOMBIES 100

#define NUMBER_LIFES 3

#define NUMBER_GUNS 3

#define NUMBER_ROADS 50

#define NUM_WAVEFORMS 2

#define NUMBER_TREES 1000

#define NUMBER_CARS 5


#define PUSH 100

struct resources_s{
    SDL_Texture* background;
    SDL_Texture* sprite;
    SDL_Texture* zombie;
    //SDL_Texture* zombie_flipped;
    SDL_Texture* vies;
    SDL_Texture* gun;
    SDL_Texture* road;
    SDL_Texture* bullet;
    SDL_Texture* tree;
    SDL_Texture* car;
    SDL_Texture* menu;
    SDL_Texture* play_button;
    SDL_Texture* exit_button;
    SDL_Texture* new_game_button;
    SDL_Texture* settings_button;
    TTF_Font* font;
};
typedef struct resources_s resources_t;

#endif //V1_CONSTANTS_H
