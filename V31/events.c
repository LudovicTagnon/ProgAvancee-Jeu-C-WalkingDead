//
// Created by ludovic on 24/09/2021.
//

#include "events.h"
#include "constants.h"
#include "data.h"
#include "colision.h"
#include "liste.h"
#include "audio.h"


void handle_events(SDL_Event *event, SDL_Renderer *renderer, world_t *world, resources_t *textures, Mix_Chunk *_sample[2],
              FILE *file) {

    while (SDL_PollEvent(event)) {

        if (world->quit_menu == 0) {
            if (event->type == SDL_MOUSEMOTION) {
                world->mouse.position.x = event->button.x;
                world->mouse.position.y = event->button.y;
            }
            if (event->type == SDL_MOUSEBUTTONDOWN) {
                if (sprites_collide(&world->mouse, &world->new_game_menu)) {
                    world->quit_menu = 1;
                }
            }
            if (event->type == SDL_MOUSEBUTTONDOWN) {
                if (sprites_collide(&world->mouse, &world->play_menu)) {
                    loadgame(file, world);
                    world->quit_menu = 1;
                }
            }
            if (event->type == SDL_MOUSEBUTTONDOWN) {
                if (sprites_collide(&world->mouse, &world->exit_menu)) {
                    world->gameover = 1;
                }
            }
            if (event->type == SDL_KEYDOWN) {
                if (event->key.keysym.sym == SDLK_p) {
                    play_pause_music();
                }
            }
        } else {
            if (event->type == SDL_MOUSEBUTTONDOWN) {
                if(world->c_d!=1)
                {
                    if (event->button.button == SDL_BUTTON_LEFT) {
                        if (world->c_s == 1) {

                            Mix_PlayChannel(-1, _sample[0], 0);

                            sprite_t tmp_sprite;
                            int x, y;
                            int dir;
                            if (world->Rick.text_dir == 3) {
                                x = world->Rick.position.x - 75;
                                y = world->Rick.position.y + 17;
                                dir = 3;
                            } else if (world->Rick.text_dir == 1) {
                                x = world->Rick.position.x + 75;
                                y = world->Rick.position.y + 17;
                                dir = 1;
                            } else if (world->Rick.text_dir == 2) {
                                x = world->Rick.position.x + 20;
                                y = world->Rick.position.y + 30;
                                dir = 2;
                            } else if (world->Rick.text_dir == 0) {
                                x = world->Rick.position.x;
                                y = world->Rick.position.y - 100;
                                dir = 0;
                            }

                            tmp_sprite = init_sprite(tmp_sprite, x, y, 16, 16, 30);
                            tmp_sprite.dir = dir;
                            world->nb_bullets++;
                            world->bullet = ajouterEnFin(world->bullet, tmp_sprite);
                        }
                    }
                }
            }

            if (event->type == SDL_KEYDOWN) {

                if (event->key.keysym.sym == SDLK_w) {
                    world->Rick.dir = 0;
                    world->Rick.text_dir = 0;
                    move_all_except_rick(event, world, renderer, textures);
                } else if (event->key.keysym.sym == SDLK_d) {
                    world->Rick.dir = 1;
                    world->Rick.text_dir = 1;
                    move_all_except_rick(event, world, renderer, textures);
                } else if (event->key.keysym.sym == SDLK_s) {
                    world->Rick.dir = 2;
                    world->Rick.text_dir = 2;
                    move_all_except_rick(event, world, renderer, textures);
                } else if (event->key.keysym.sym == SDLK_a) {
                    world->Rick.dir = 3;
                    world->Rick.text_dir = 3;

                    move_all_except_rick(event, world, renderer, textures);

                } else if (event->key.keysym.sym == SDLK_f) {
                    if(world->c_d==1){
                        world->c_d =0;
                        world->Rick.speed/=3;
                        world->Rick.w = 138;
                        world->Rick.h = 248;
                        world->current_car->position.x = world->Rick.position.x;
                        world->current_car->position.y = world->Rick.position.y+400;
                        world->current_car->disappear = 0;
                        world->current_car->dir = world->Rick.dir;
                        world->current_car->text_dir = world->Rick.text_dir;
                    }
                    else
                    {
                        list_t tmp_gun, tmp_car, tmp_food;
                        tmp_gun = world->Gun;
                        tmp_car = world->Car;
                        tmp_food = world->Chicken;
                        while (tmp_gun != NULL || tmp_car != NULL || tmp_food != NULL) {

                            if(tmp_gun != NULL){
                                handle_Rick_Weapon_collision(event, world, textures, renderer, &world->Rick, &tmp_gun->val);
                                tmp_gun = tmp_gun->nxt;
                            }
                            if(tmp_car != NULL){
                                handle_Rick_Car_collision(event, world, textures, renderer, &world->Rick, &tmp_car->val);
                                tmp_car = tmp_car->nxt;
                            }
                            if(tmp_food != NULL){
                                if(tmp_food->val.life<=0){
                                    handle_Rick_Food_collision(world,&world->Rick,&tmp_food->val);
                                }
                                tmp_food = tmp_food->nxt;
                            }
                        }
                    }
                    //free(tmp_gun);
                } else if (event->key.keysym.sym == SDLK_p) {
                    play_pause_music();
                } else if (event->key.keysym.sym == SDLK_ESCAPE) {
                    world->quit_menu = 0;
                }
                if (event->key.keysym.sym == SDLK_LSHIFT) {
                    world->Rick.speed *= 2;
                }
            } else if (event->type == SDL_KEYUP) {
                if (event->key.keysym.sym == SDLK_LSHIFT) {
                    world->Rick.speed /= 2;
                }
            }
        }
    }
}