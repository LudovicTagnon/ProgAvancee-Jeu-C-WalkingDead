//
// Created by ludovic on 24/09/2021.
//

#ifndef V1_GRAPHICS_H
#define V1_GRAPHICS_H

//=========================================

#include "constants.h"
#include "data.h"
#include "audio.h"
#include "liste.h"


//=========================================

void init_textures(SDL_Renderer *renderer, resources_t *textures, world_t *world);

void refresh_menu(SDL_Renderer *renderer, world_t *world, resources_t *textures);

void refresh_graphics(SDL_Renderer *renderer, world_t *world,resources_t *textures);

void apply_background(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite);

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite);

void clean(SDL_Window *window, SDL_Renderer *renderer, resources_t *textures, world_t *world, Mix_Chunk *_sample[NUM_WAVEFORMS]);

void clean_textures(resources_t *textures);

void apply_terrain(SDL_Renderer *renderer, world_t *world,resources_t *textures);

list_t liste_affichage_ordre(world_t *world);

void quicksort(sprite_t sprite[10000],int first,int last);
//=========================================

#endif //V1_GRAPHICS_H
