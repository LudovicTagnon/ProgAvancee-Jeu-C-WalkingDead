//
// Created by ludovic on 24/09/2021.
//

#include "events.h"
#include "graphics.h"


void handle_events(SDL_Event *event, SDL_Renderer *renderer, world_t *world, resources_t *textures) {
    while (SDL_PollEvent(event)) {

        if (event->type == SDL_QUIT) {
            //On indique la fin du jeu
            world->gameover = 1;
        }

        if (event->type == SDL_KEYDOWN) {

            if (event->key.keysym.sym == SDLK_ESCAPE) {
                world->gameover = 1;
            }


            else if (event->key.keysym.sym == SDLK_w) {
                world->Rick.dir=0;
                move_all_except_rick(world);
            }
            else if (event->key.keysym.sym == SDLK_d) {
                if (world->Rick.dir != 1) {
                    textures->sprite = charger_image_transparente("img/rick_flipped.bmp", renderer);
                    world->Rick.dir = 1;
                }
                else {
                    move_all_except_rick(world);
                }

            }
            else if (event->key.keysym.sym == SDLK_s) {
                world->Rick.dir=2;
                move_all_except_rick(world);
            }
            else if (event->key.keysym.sym == SDLK_a) {

                if (world->Rick.dir != 3) {
                    textures->sprite = charger_image_transparente("img/rick.bmp", renderer);
                    world->Rick.dir = 3;
                }
                else {
                    move_all_except_rick(world);
                }
            }


        }
    }
}