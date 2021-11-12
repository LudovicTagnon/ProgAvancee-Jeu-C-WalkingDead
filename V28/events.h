//
// Created by ludovic on 24/09/2021.
//

#ifndef V1_EVENTS_H
#define V1_EVENTS_H

#include <SDL2/SDL_mixer.h>
#include "constants.h"
#include "data.h"

void handle_events(SDL_Event *event, SDL_Renderer *renderer, world_t *world, resources_t *textures, Mix_Chunk *_sample[2], FILE* file) ;

#endif //V1_EVENTS_H
