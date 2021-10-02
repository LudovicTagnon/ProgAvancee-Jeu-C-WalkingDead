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


            for(int i=0; i<NUMBER_ZOMBIES; i++){
                print_position(&world->Zombie[i].position);
            }

            if (event->key.keysym.sym == SDLK_ESCAPE) {
                world->gameover = 1;
            } else if (event->key.keysym.sym == SDLK_UP) {
                //world->position.y--;
                move_all_except_rick(world, 0);
            } else if (event->key.keysym.sym == SDLK_RIGHT) {
                //world->position.x-=STEP;
                if (world->Rick.dir == 0) {
                    textures->sprite = charger_image_transparente("img/rick_flipped.bmp", renderer);
                    world->Rick.dir = 1;
                } else {
                    move_all_except_rick(world, 1);
                }

            } else if (event->key.keysym.sym == SDLK_DOWN) {
                //world->position.y++;
                move_all_except_rick(world, 2);
            } else if (event->key.keysym.sym == SDLK_LEFT) {
                //world->position.x+=STEP;

                if (world->Rick.dir == 1) {
                    textures->sprite = charger_image_transparente("img/rick.bmp", renderer);
                    world->Rick.dir = 0;
                } else {
                    move_all_except_rick(world, 3);
                }

            }


            //print_position(&world->Background.position);
            //print_sprite(&world->Rick);


        }
    }
}