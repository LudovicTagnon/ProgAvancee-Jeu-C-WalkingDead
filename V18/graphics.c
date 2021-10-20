//
// Created by ludovic on 24/09/2021.
//

#include "graphics.h"


void init_textures(SDL_Renderer *renderer, resources_t *textures, world_t *world) {
    textures->background = charger_image("img/grass2.bmp", renderer);
    textures->sprite = charger_image_transparente("img/rick.bmp", renderer);
    textures->zombie = charger_image_transparente("img/zombie.bmp", renderer);
    //textures->zombie_flipped = charger_image_transparente("img/zombie_flipped.bmp", renderer);
    textures->vies = charger_image_transparente("img/life.bmp", renderer);
    textures->gun = charger_image_transparente("img/gun.bmp", renderer);
    textures->road = charger_image_transparente("img/road.bmp", renderer);
    textures->bullet = charger_image_transparente("img/bullet.bmp", renderer);
    textures->menu = charger_image("img/menu.bmp", renderer);
    textures->play_button = charger_image_transparente("img/play.bmp", renderer);
    textures->new_game_button = charger_image_transparente("img/new_game.bmp", renderer);
    textures->settings_button = charger_image_transparente("img/settings.bmp", renderer);
    textures->exit_button = charger_image_transparente("img/exit.bmp", renderer);
}

void refresh_menu(SDL_Renderer *renderer, world_t *world, resources_t *textures){
    clear_renderer(renderer);
    apply_sprite(renderer, textures->menu, &world->Menu);
    apply_sprite(renderer, textures->play_button, &world->play_menu);
    apply_sprite(renderer, textures->new_game_button, &world->new_game_menu);
    apply_sprite(renderer, textures->settings_button, &world->settings_menu);
    apply_sprite(renderer, textures->exit_button, &world->exit_menu);
    update_screen(renderer);
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *textures) {
    //printf("4.0\n");

    //on vide le renderer
    clear_renderer(renderer);
    //printf("4.1\n");

    apply_terrain(renderer, world, textures);
    //printf("4.2\n");

    list_t tmp_road = world->Road;
    while (tmp_road != NULL) {
        apply_sprite(renderer, textures->road, &tmp_road->val);
        tmp_road = tmp_road->nxt;
    }

    list_t tmp_gun = world->Gun;
    while (tmp_gun != NULL) {
        if (tmp_gun->val.disappear == 0) {
            apply_sprite(renderer, textures->gun, &tmp_gun->val);
        }
        tmp_gun = tmp_gun->nxt;
    }


    //printf("4.3\n");

    list_t tmp_zombie = world->Zombie;
    while (tmp_zombie != NULL) {
        if (distance(tmp_zombie->val, world->Rick) < 3 * SCREEN_HEIGHT) {
            if (tmp_zombie->val.life <= 0) {
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

    //application de la texture de Rick dans le renderer
    if (world->Rick.disappear == 0) {
        apply_sprite(renderer, textures->sprite, &world->Rick);
    }

    //printf("4.4\n");

    list_t tmp_vie = world->vies;
    for (int i = 0; i < world->nb_vies_restantes; i++) {
        apply_sprite(renderer, textures->vies, &tmp_vie->val);
        tmp_vie = tmp_vie->nxt;
    }

    //printf("4.5\n");
    //printf("%i\n", world->nb_bullets);
    if (world->nb_bullets != 0) {
        list_t tmp_bullet = world->bullet;
        for (int i = 0; i < world->nb_bullets; i++) {
            if (distance(tmp_bullet->val, world->Rick) < 3 * SCREEN_HEIGHT) {

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

    //printf("4.6\n");

    // on met à jour l'écran
    update_screen(renderer);
    //printf("4.7\n");
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
}

void clean_textures(resources_t *textures) {
    clean_texture(textures->background);
    clean_texture(textures->sprite);
    clean_texture(textures->zombie);
    clean_texture(textures->vies);
    clean_texture(textures->gun);
    clean_texture(textures->road);
    clean_texture(textures->bullet);
}


void apply_terrain(SDL_Renderer *renderer, world_t *world, resources_t *textures) {
    for (int i = 0; i < TERRAIN_SIZE; i++) {
        for (int j = 0; j < TERRAIN_SIZE; j++) {
            world->Background.position.x += GRASS_WIDTH;
            apply_background(renderer, textures->background, (&world->Background));
        }
        world->Background.position.x -= world->Background.w;
        world->Background.position.y += GRASS_HEIGHT;
    }
    world->Background.position.y -= (world->Background.h);
}
