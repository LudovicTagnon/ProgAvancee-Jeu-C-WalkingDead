//
// Created by ludovic on 24/09/2021.
//

#ifndef V1_EVENTS_H
#define V1_EVENTS_H

#include "constants.h"
#include "data.h"

void handle_events(SDL_Event *event, SDL_Renderer *renderer, world_t *world, resources_t *textures, wav_device_t* wav_device_ptr) ;

#endif //V1_EVENTS_H
