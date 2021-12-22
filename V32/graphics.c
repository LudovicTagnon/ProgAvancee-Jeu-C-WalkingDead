//
// Created by ludovic on 24/09/2021.
//

#include "graphics.h"


void init_textures(SDL_Renderer *renderer, resources_t *textures, world_t *world) {
    textures->font = load_font("font/arial.ttf", 200);
    textures->background = charger_image_transparente("img/grass2.bmp", renderer);

    textures->rick_left = charger_image_transparente("img/rick_left.bmp", renderer);
    textures->rick_right = charger_image_transparente("img/rick_right.bmp", renderer);
    textures->rick_front = charger_image_transparente("img/rick_front.bmp", renderer);
    textures->rick_back = charger_image_transparente("img/rick_back.bmp", renderer);
    textures->rick_gun_left = charger_image_transparente("img/rick_gun_left.bmp", renderer);
    textures->rick_gun_right = charger_image_transparente("img/rick_gun_right.bmp", renderer);
    textures->rick_gun_front = charger_image_transparente("img/rick_gun_front.bmp", renderer);
    textures->rick_gun_back = charger_image_transparente("img/rick_gun_back.bmp", renderer);

    textures->zombie_left = charger_image_transparente("img/zombie_left.bmp", renderer);
    textures->zombie_right = charger_image_transparente("img/zombie_right.bmp", renderer);
    textures->dead_zombie_left = charger_image_transparente("img/dead_zombie_left.bmp", renderer);
    textures->dead_zombie_right = charger_image_transparente("img/dead_zombie_right.bmp", renderer);

    textures->chicken_left = charger_image_transparente("img/Chicken_left.bmp", renderer);
    textures->chicken_right = charger_image_transparente("img/Chicken_right.bmp", renderer);
    textures->chicken_food = charger_image_transparente("img/Chicken_food.bmp", renderer);

    textures->blood = charger_image_transparente("img/blood.bmp", renderer);

    textures->vies = charger_image_transparente("img/life.bmp", renderer);
    textures->faim = charger_image_transparente("img/faim.bmp", renderer);
    textures->gun = charger_image_transparente("img/gun.bmp", renderer);
    textures->road = charger_image_transparente("img/road.bmp", renderer);

    textures->bullet_up = charger_image_transparente("img/bullet_up.bmp", renderer);
    textures->bullet_right = charger_image_transparente("img/bullet_right.bmp", renderer);
    textures->bullet_down = charger_image_transparente("img/bullet_down.bmp", renderer);
    textures->bullet_left = charger_image_transparente("img/bullet_left.bmp", renderer);

    textures->tree = charger_image_transparente("img/tree.bmp", renderer);
    textures->menu = charger_image_transparente("img/menu.bmp", renderer);
    textures->play_button = charger_image_transparente("img/play.bmp", renderer);
    textures->new_game_button = charger_image_transparente("img/new_game.bmp", renderer);
    textures->settings_button = charger_image_transparente("img/settings.bmp", renderer);
    textures->exit_button = charger_image_transparente("img/exit.bmp", renderer);

    textures->car_up = charger_image_transparente("img/car_up.bmp", renderer);
    textures->car_right = charger_image_transparente("img/car_right.bmp", renderer);
    textures->car_down = charger_image_transparente("img/car_down.bmp", renderer);
    textures->car_left = charger_image_transparente("img/car_left.bmp", renderer);

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


    list_t tmp_tree = world->tree;
    while (tmp_tree != NULL) {
        if (distance(tmp_tree->val, world->Rick) < 2 * SCREEN_HEIGHT) {
            apply_sprite(renderer, textures->tree, &tmp_tree->val);
        }
        tmp_tree = tmp_tree->nxt;
    }


    list_t tmp_chicken = world->Chicken;
    while (tmp_chicken != NULL) {
        if (distance(tmp_chicken->val, world->Rick) < 2 * SCREEN_HEIGHT) {

            if (tmp_chicken->val.life <= 0) {
                sprite_t tmp_chicken_food = tmp_chicken->val;
                tmp_chicken_food.position.x+=40;
                tmp_chicken_food.position.y+=50;
                apply_sprite(renderer, textures->blood, &tmp_chicken->val);
                if(tmp_chicken->val.disappear!=2){
                    apply_sprite(renderer, textures->chicken_food, &tmp_chicken_food);
                }
            } else { //pas mort
                if (tmp_chicken->val.dir == 3) {
                    apply_sprite(renderer, textures->chicken_left, &tmp_chicken->val);
                } else {
                    apply_sprite(renderer, textures->chicken_right, &tmp_chicken->val);
                }
            }

        }
        tmp_chicken = tmp_chicken->nxt;
    }

    list_t tmp_car = world->Car;
    while (tmp_car != NULL) {
        if (tmp_car->val.disappear == 0) {
            if (distance(tmp_car->val, world->Rick) < 2 * SCREEN_HEIGHT) {
                if(tmp_car->val.dir == 0){
                    apply_sprite(renderer, textures->car_up, &tmp_car->val);
                }
                else if(tmp_car->val.dir == 1){
                    apply_sprite(renderer, textures->car_right, &tmp_car->val);
                }
                else if(tmp_car->val.dir == 2){
                    apply_sprite(renderer, textures->car_down, &tmp_car->val);
                }
                else if(tmp_car->val.dir == 3){
                    apply_sprite(renderer, textures->car_left, &tmp_car->val);
                }
            }
        }
        tmp_car = tmp_car->nxt;
    }

    list_t tmp_zombie = world->Zombie;
    while (tmp_zombie != NULL) {
        if (distance(tmp_zombie->val, world->Rick) < 2 * SCREEN_HEIGHT) {

            if (tmp_zombie->val.life <= 0) {
                if(tmp_zombie->val.dir == 3){
                    apply_sprite(renderer, textures->blood, &tmp_zombie->val);
                    apply_sprite(renderer, textures->dead_zombie_left, &tmp_zombie->val);
                }else{
                    apply_sprite(renderer, textures->blood, &tmp_zombie->val);
                    apply_sprite(renderer, textures->dead_zombie_right, &tmp_zombie->val);
                }
            } else {
                if (tmp_zombie->val.dir == 3) {
                    apply_sprite(renderer, textures->zombie_left, &tmp_zombie->val);
                } else {
                    apply_sprite(renderer, textures->zombie_right, &tmp_zombie->val);
                }
            }

        }
        tmp_zombie = tmp_zombie->nxt;
    }

    if (world->Rick.disappear == 0) {

        if(world->c_d==1){
            if(world->Rick.dir==0)
            {
                apply_sprite(renderer, textures->car_up, &world->Rick);
            }
            else if(world->Rick.dir==1){
                apply_sprite(renderer, textures->car_right, &world->Rick);
            }
            else if(world->Rick.dir==2){
                apply_sprite(renderer, textures->car_down, &world->Rick);
            }
            else if(world->Rick.dir==3){
                apply_sprite(renderer, textures->car_left, &world->Rick);
            }
        }
        else if(world->c_s==0)
        {
            if(world->Rick.dir==0)
            {
                apply_sprite(renderer, textures->rick_back, &world->Rick);
            }
            else if(world->Rick.dir==1){
                apply_sprite(renderer, textures->rick_right, &world->Rick);
            }
            else if(world->Rick.dir==2){
                apply_sprite(renderer, textures->rick_front, &world->Rick);
            }
            else if(world->Rick.dir==3){
                apply_sprite(renderer, textures->rick_left, &world->Rick);
            }
        }
        else if(world->c_s==1){
            if(world->Rick.dir==0)
            {
                apply_sprite(renderer, textures->rick_gun_back, &world->Rick);
            }
            else if(world->Rick.dir==1){
                apply_sprite(renderer, textures->rick_gun_right, &world->Rick);
            }
            else if(world->Rick.dir==2){
                apply_sprite(renderer, textures->rick_gun_front, &world->Rick);
            }
            else if(world->Rick.dir==3){
                apply_sprite(renderer, textures->rick_gun_left, &world->Rick);
            }
        }
    }



    if (world->nb_bullets != 0) {
        list_t tmp_bullet = world->bullet;
        for (int i = 0; i < world->nb_bullets; i++) {
            if (distance(tmp_bullet->val, world->Rick) < 2 * SCREEN_HEIGHT) {

                if (tmp_bullet->val.dir == 3) {
                    apply_sprite(renderer, textures->bullet_left, &tmp_bullet->val);
                } else if (tmp_bullet->val.dir == 1) {
                    apply_sprite(renderer, textures->bullet_right, &tmp_bullet->val);
                } else if (tmp_bullet->val.dir == 2) {
                    apply_sprite(renderer, textures->bullet_down, &tmp_bullet->val);
                } else if (tmp_bullet->val.dir == 0) {
                    apply_sprite(renderer, textures->bullet_up, &tmp_bullet->val);
                }
            }
            tmp_bullet = tmp_bullet->nxt;
        }
    }

    list_t tmp_vie = world->vies;
    for (int i = 0; i < world->nb_vies_restantes; i++) {
        apply_sprite(renderer, textures->vies, &tmp_vie->val);
        tmp_vie = tmp_vie->nxt;
    }

    list_t tmp_faim = world->faim;
    for (int i = 0; i < world->nb_faim_restant; i++) {
        if(tmp_faim->val.disappear==0){
            apply_sprite(renderer, textures->faim, &tmp_faim->val);
        }
        tmp_faim = tmp_faim->nxt;
    }

    char nb_zombies_killed[4];
    sprintf(nb_zombies_killed, "%d", world->nb_zombies_killed);
    SDL_Color color = { 255, 0, 255 };
    apply_text(renderer, 50, 50, 50, 50, nb_zombies_killed, textures->font, color);

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

    clean_texture(textures->rick_left);
    clean_texture(textures->rick_right);
    clean_texture(textures->rick_front);
    clean_texture(textures->rick_back);

    clean_texture(textures->rick_gun_right);
    clean_texture(textures->rick_gun_left);
    clean_texture(textures->rick_gun_back);
    clean_texture(textures->rick_gun_front);

    clean_texture(textures->zombie_left);
    clean_texture(textures->zombie_right);

    clean_texture(textures->dead_zombie_right);
    clean_texture(textures->dead_zombie_left);

    clean_texture(textures->chicken_left);
    clean_texture(textures->chicken_right);
    clean_texture(textures->chicken_food);

    clean_texture(textures->vies);
    clean_texture(textures->faim);
    clean_texture(textures->gun);
    clean_texture(textures->road);

    clean_texture(textures->bullet_left);
    clean_texture(textures->bullet_right);
    clean_texture(textures->bullet_down);
    clean_texture(textures->bullet_up);

    clean_texture(textures->tree);

    clean_texture(textures->car_left);
    clean_texture(textures->car_right);
    clean_texture(textures->car_down);
    clean_texture(textures->car_up);

    clean_texture(textures->menu);
    clean_texture(textures->play_button);
    clean_texture(textures->new_game_button);
    clean_texture(textures->settings_button);
    clean_texture(textures->exit_button);

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
