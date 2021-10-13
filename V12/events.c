//
// Created by ludovic on 24/09/2021.
//

#include "events.h"
#include "constants.h"
#include "data.h"
#include "liste.h"


void handle_events(SDL_Event *event, SDL_Renderer *renderer, world_t *world, resources_t *textures, wav_device_t* wav_device_ptr) {
    while (SDL_PollEvent(event)) {

        if (event->type == SDL_QUIT) {
            //On indique la fin du jeu
            world->gameover = 1;
        }

        if(event->type == SDL_MOUSEBUTTONDOWN){
            if(event->button.button == SDL_BUTTON_LEFT) {
                if (world->c_s == 1) {

                    play_audio(event, renderer, world, textures, wav_device_ptr);


                    sprite_t tmp_sprite;
                    int x, y;
                    int dir;
                    if(world->Rick.text_dir==3){
                        x = world->Rick.position.x - 75;
                        y = world->Rick.position.y + 17;
                        dir=3;
                    }else{
                        x = world->Rick.position.x + 75;
                        y = world->Rick.position.y + 17;
                        dir=1;
                    }

                    tmp_sprite = init_sprite(tmp_sprite, x, y, 16, 16, 30);
                    tmp_sprite.dir = dir;
                    world->nb_bullets++;
                    world->bullet = ajouterEnFin(world->bullet, tmp_sprite);
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
                    if(world->c_s==1){
                        textures->sprite = charger_image_transparente("img/rick_gun_flipped.bmp", renderer);
                    }else{
                        textures->sprite = charger_image_transparente("img/rick_flipped.bmp", renderer);
                    }
                    world->Rick.dir = 1;
                    world->Rick.text_dir = 1;
                    move_all_except_rick(event, world);
            }

            else if (event->key.keysym.sym == SDLK_s) {
                world->Rick.dir=2;
                move_all_except_rick(event, world);
            }

            else if (event->key.keysym.sym == SDLK_a) {

                    if(world->c_s==1){
                        textures->sprite = charger_image_transparente("img/rick_gun.bmp", renderer);
                    }else{
                        textures->sprite = charger_image_transparente("img/rick.bmp", renderer);
                    }
                    world->Rick.dir = 3;
                    world->Rick.text_dir = 3;

                    move_all_except_rick(event, world);

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