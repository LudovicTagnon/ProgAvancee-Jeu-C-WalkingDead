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

        if(event->type == SDL_MOUSEBUTTONDOWN){
            if(event->button.button == SDL_BUTTON_LEFT) {
                if (world->c_s == 1) {
                    
                }
            }
        }

        if (event->type == SDL_KEYDOWN) {
            if (event->key.keysym.sym == SDLK_ESCAPE) {
                world->gameover = 1;
            }

            else if (event->key.keysym.sym == SDLK_w) {
                world->Rick.dir=0;
                move_all_except_rick(event, world);
            }
            else if (event->key.keysym.sym == SDLK_d) {
                if (world->Rick.dir != 1) {
                    if(world->c_s==1){
                        textures->sprite = charger_image_transparente("img/rick_gun_flipped.bmp", renderer);
                    }else{
                        textures->sprite = charger_image_transparente("img/rick_flipped.bmp", renderer);
                    }
                    world->Rick.dir = 1;
                }
                else {
                    move_all_except_rick(event, world);
                }

            }
            else if (event->key.keysym.sym == SDLK_s) {
                world->Rick.dir=2;
                move_all_except_rick(event, world);
            }
            else if (event->key.keysym.sym == SDLK_a) {

                if (world->Rick.dir != 3) {
                    if(world->c_s==1){
                        textures->sprite = charger_image_transparente("img/rick_gun.bmp", renderer);
                    }else{
                        textures->sprite = charger_image_transparente("img/rick.bmp", renderer);
                    }
                    world->Rick.dir = 3;
                }
                else {
                    move_all_except_rick(event, world);
                }
            }
            else if (event->key.keysym.sym == SDLK_f){
                list_t tmp_gun;
                tmp_gun = world->Gun;
                while (tmp_gun != NULL) {
                    handle_Rick_Weapon_collision(event, world, textures, renderer, &world->Rick, &tmp_gun->val);
                    tmp_gun = tmp_gun->nxt;
                }
                free(tmp_gun);
            }


        }
    }
}