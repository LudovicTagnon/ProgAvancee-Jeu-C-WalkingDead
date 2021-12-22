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

#define NUMBER_ZOMBIES 1000

#define NUMBER_LIFES 10

#define NUMBER_GUNS 3

#define NUMBER_ROADS 100

#define NUM_WAVEFORMS 2

#define NUMBER_TREES 200

#define NUMBER_CARS 5

#define NUMBER_CHICKEN 50

#define PUSH 100

struct resources_s{ //31 textures + 1 font
    SDL_Texture* background;

    SDL_Texture* rick_left;
    SDL_Texture* rick_right;
    SDL_Texture* rick_front;
    SDL_Texture* rick_back;

    SDL_Texture* rick_gun_left;
    SDL_Texture* rick_gun_right;
    SDL_Texture* rick_gun_front;
    SDL_Texture* rick_gun_back;

    SDL_Texture* rick_dead;

    SDL_Texture* zombie_left;
    SDL_Texture* zombie_right;
    SDL_Texture* dead_zombie_left;
    SDL_Texture* dead_zombie_right;

    SDL_Texture* chicken_left;
    SDL_Texture* chicken_right;
    SDL_Texture* chicken_food;

    SDL_Texture* vies;
    SDL_Texture* faim;
    SDL_Texture* gun;
    SDL_Texture* road;

    SDL_Texture* bullet_up;
    SDL_Texture* bullet_right;
    SDL_Texture* bullet_down;
    SDL_Texture* bullet_left;

    SDL_Texture* tree;

    SDL_Texture* car_up;
    SDL_Texture* car_right;
    SDL_Texture* car_down;
    SDL_Texture* car_left;

    SDL_Texture* menu;
    SDL_Texture* play_button;
    SDL_Texture* exit_button;
    SDL_Texture* new_game_button;
    SDL_Texture* settings_button;
    SDL_Texture* blood;
    TTF_Font* font;
};
typedef struct resources_s resources_t;

#endif //V1_CONSTANTS_H
