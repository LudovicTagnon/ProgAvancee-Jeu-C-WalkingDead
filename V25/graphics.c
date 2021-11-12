//
// Created by ludovic on 24/09/2021.
//

#include "graphics.h"


void init_textures(SDL_Renderer *renderer, resources_t *textures, world_t *world) {
    textures->font = load_font("font/arial.ttf", 200);
    textures->background = charger_image("img/grass2.bmp", renderer);
    textures->sprite = charger_image_transparente("img/rick.bmp", renderer);
    textures->zombie = charger_image_transparente("img/zombie.bmp", renderer);
    //textures->zombie_flipped = charger_image_transparente("img/zombie_flipped.bmp", renderer);
    textures->vies = charger_image_transparente("img/life.bmp", renderer);
    textures->gun = charger_image_transparente("img/gun.bmp", renderer);
    textures->road = charger_image_transparente("img/road.bmp", renderer);
    textures->bullet = charger_image_transparente("img/bullet.bmp", renderer);
    textures->tree = charger_image_transparente("img/tree.bmp", renderer);
    textures->menu = charger_image("img/menu.bmp", renderer);
    textures->play_button = charger_image_transparente("img/play.bmp", renderer);
    textures->new_game_button = charger_image_transparente("img/new_game.bmp", renderer);
    textures->settings_button = charger_image_transparente("img/settings.bmp", renderer);
    textures->exit_button = charger_image_transparente("img/exit.bmp", renderer);
    textures->car = charger_image_transparente("img/car_up.bmp", renderer);

}

void refresh_menu(SDL_Renderer *renderer, world_t *world, resources_t *textures) {
    clear_renderer(renderer);
    apply_sprite(renderer, textures->menu, &world->Menu);
    apply_sprite(renderer, textures->play_button, &world->play_menu);
    apply_sprite(renderer, textures->new_game_button, &world->new_game_menu);
    apply_sprite(renderer, textures->settings_button, &world->settings_menu);
    apply_sprite(renderer, textures->exit_button, &world->exit_menu);
    update_screen(renderer);
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *textures) {

    //on vide le renderer
    clear_renderer(renderer);

    int tree_flag=0; // rick devant ou derriere l'arbre
    if( world->Rick.h + world->Rick.position.y  > 600 + world->current_tree->position.y  ){
        tree_flag = 1; // rick devant l'arbre
    }
    else {
        tree_flag = 0; // rick derriere l'arbre
    }

    apply_terrain(renderer, world, textures);

    list_t tmp_road = world->Road;
    while (tmp_road != NULL) {
        if (distance(tmp_road->val, world->Rick) < 2 * SCREEN_HEIGHT) {
            apply_sprite(renderer, textures->road, &tmp_road->val);
        }
        tmp_road = tmp_road->nxt;
    }


    list_t tmp_gun = world->Gun;
    while (tmp_gun != NULL) {
        if (tmp_gun->val.disappear == 0) {
            if (distance(tmp_gun->val, world->Rick) < 2 * SCREEN_HEIGHT) {
                apply_sprite(renderer, textures->gun, &tmp_gun->val);
            }
        }
        tmp_gun = tmp_gun->nxt;
    }

    list_t tmp_car = world->Car;
    while (tmp_car != NULL) {
        if (tmp_car->val.disappear == 0) {
            if (distance(tmp_car->val, world->Rick) < 2 * SCREEN_HEIGHT) {
                if(tmp_car->val.dir == 0){
                    textures->car = charger_image_transparente("img/car_up.bmp", renderer);
                }else if(tmp_car->val.dir == 1){
                    textures->car = charger_image_transparente("img/car_right.bmp", renderer);
                }else if(tmp_car->val.dir == 2){
                    textures->car = charger_image_transparente("img/car_down.bmp", renderer);
                }else if(tmp_car->val.dir == 3){
                    textures->car = charger_image_transparente("img/car_left.bmp", renderer);
                }
                apply_sprite(renderer, textures->car, &tmp_car->val);
            }
        }
        tmp_car = tmp_car->nxt;
    }


    if(tree_flag == 1){
        list_t tmp_tree = world->tree;
        while (tmp_tree!=NULL){
            if (distance(tmp_tree->val, world->Rick) < 2 * SCREEN_HEIGHT) {
                apply_sprite(renderer, textures->tree, &tmp_tree->val);
            }
            tmp_tree = tmp_tree->nxt;
        }
    }


    list_t tmp_zombie = world->Zombie;
    while (tmp_zombie != NULL) {
        if (distance(tmp_zombie->val, world->Rick) < 2 * SCREEN_HEIGHT) {
            if (tmp_zombie->val.life <= 0) {
                textures->blood = charger_image_transparente("img/blood.bmp", renderer);
                apply_sprite(renderer, textures->blood, &tmp_zombie->val);
                textures->zombie = charger_image_transparente("img/dead_zombie.bmp", renderer);
                apply_sprite(renderer, textures->zombie, &tmp_zombie->val);
            } else {
                if (tmp_zombie->val.dir == 3) {
                    textures->zombie = charger_image_transparente("img/zombie_flipped.bmp", renderer);
                    apply_sprite(renderer, textures->zombie, &tmp_zombie->val);
                } else {
                    textures->zombie = charger_image_transparente("img/zombie.bmp", renderer);
                    apply_sprite(renderer, textures->zombie, &tmp_zombie->val);
                }
            }
        }
        tmp_zombie = tmp_zombie->nxt;
    }

    if (world->Rick.disappear == 0) {
        apply_sprite(renderer, textures->sprite, &world->Rick);
    }


    if(tree_flag == 0){
        list_t tmp_tree = world->tree;
        while(tmp_tree!=NULL){
            if (distance(tmp_tree->val, world->Rick) < 2 * SCREEN_HEIGHT) {
                apply_sprite(renderer, textures->tree, &tmp_tree->val);
            }
            tmp_tree = tmp_tree->nxt;
        }
    }

    list_t tmp_vie = world->vies;
    for (int i = 0; i < world->nb_vies_restantes; i++) {
        apply_sprite(renderer, textures->vies, &tmp_vie->val);
        tmp_vie = tmp_vie->nxt;
    }


    if (world->nb_bullets != 0) {
        list_t tmp_bullet = world->bullet;
        for (int i = 0; i < world->nb_bullets; i++) {
            if (distance(tmp_bullet->val, world->Rick) < 2 * SCREEN_HEIGHT) {

                if (tmp_bullet->val.dir == 3) {
                    textures->bullet = charger_image_transparente("img/bullet.bmp", renderer);
                    apply_sprite(renderer, textures->bullet, &tmp_bullet->val);
                } else if (tmp_bullet->val.dir == 1) {
                    textures->bullet = charger_image_transparente("img/bullet_flipped.bmp", renderer);
                    apply_sprite(renderer, textures->bullet, &tmp_bullet->val);
                } else if (tmp_bullet->val.dir == 2) {
                    textures->bullet = charger_image_transparente("img/bullet_down.bmp", renderer);
                    apply_sprite(renderer, textures->bullet, &tmp_bullet->val);
                } else if (tmp_bullet->val.dir == 0) {
                    textures->bullet = charger_image_transparente("img/bullet_up.bmp", renderer);
                    apply_sprite(renderer, textures->bullet, &tmp_bullet->val);
                }
            }
            tmp_bullet = tmp_bullet->nxt;
        }
    }


    char nb_zombies_killed[4];
    sprintf(nb_zombies_killed, "%d", world->nb_zombies_killed);

    //char time[12];
    //sprintf(time,"%u", SDL_GetTicks());
    apply_text(renderer, 50, 50, 50, 50, nb_zombies_killed, textures->font, (SDL_Color) {250, 0, 0});

    // on met à jour l'écran
    update_screen(renderer);

}


void apply_background(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite) {
    if (texture != NULL) {
        apply_texture(texture, renderer, (sprite->position.x), (sprite->position.y));
    }
}


void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite) {
    if (texture != NULL) {
        apply_texture(texture, renderer,
                      (sprite->position.x) - ((sprite->w) / 2),
                      (sprite->position.y) - ((sprite->h) / 2)
        );
    }
}

void clean(SDL_Window *window, SDL_Renderer *renderer, resources_t *textures, world_t *world, Mix_Chunk *_sample[NUM_WAVEFORMS]) {
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer, window);
    clean_audio(_sample);
    TTF_Quit();
}

void clean_textures(resources_t *textures) {
    clean_texture(textures->background);
    clean_texture(textures->sprite);
    clean_texture(textures->zombie);
    clean_texture(textures->vies);
    clean_texture(textures->gun);
    clean_texture(textures->road);
    clean_texture(textures->bullet);
    clean_font(textures->font);
}


void apply_terrain(SDL_Renderer *renderer, world_t *world, resources_t *textures) {
    sprite_t tmp_background = world->Background;
    tmp_background.position.x -=  TERRAIN_SIZE*GRASS_WIDTH/2;
    tmp_background.position.y -=  TERRAIN_SIZE*GRASS_HEIGHT/2;

    for (int i = 0; i < TERRAIN_SIZE ; i++) {
        for (int j = 0; j < TERRAIN_SIZE ; j++) {
            if(distance(tmp_background, world->Rick) <  1.5*SCREEN_WIDTH) {
                apply_background(renderer, textures->background, &tmp_background);
            }
            tmp_background.position.x += GRASS_WIDTH ;
        }
        tmp_background.position.x -= world->Background.w * TERRAIN_SIZE;
        tmp_background.position.y += GRASS_HEIGHT ;
    }
    tmp_background.position.y -= (world->Background.h) * TERRAIN_SIZE;
}
