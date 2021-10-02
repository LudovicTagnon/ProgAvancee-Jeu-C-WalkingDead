//
// Created by ludovic on 24/09/2021.
//

#include "graphics.h"
#include "events.h"


void init_textures(SDL_Renderer *renderer, resources_t *textures) {
    textures->background = charger_image("img/grass.bmp", renderer);
    textures->sprite = charger_image_transparente("img/rick.bmp", renderer);
    textures->zombie = charger_image_transparente("img/zombie.bmp", renderer);
    textures->zombie_flipped = charger_image_transparente("img/zombie_flipped.bmp", renderer);
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *textures) {
    //printf("4.0\n");

    //on vide le renderer
    clear_renderer(renderer);
    //printf("4.1\n");

    apply_terrain(renderer, world, textures);
    //printf("4.2\n");

    //application de la texture de Rick dans le renderer
    apply_sprite(renderer, textures->sprite, &world->Rick);
    //printf("4.3\n");

    //application de la texture du sprite (vaisseau) dans le renderer
    for (int i = 0; i < NUMBER_ZOMBIES; i++) {
        if(world->Zombie[i].dir==0){
            apply_sprite(renderer, textures->zombie_flipped, &world->Zombie[i]);
        }
        else if (world->Zombie[i].dir==1){
            apply_sprite(renderer, textures->zombie, &world->Zombie[i]);
        }
        else{
            apply_sprite(renderer, textures->zombie, &world->Zombie[i]);
        }
    }
    //printf("RICK: x=%i y=%i\n", world->Rick.position.x, world->Rick.position.y);
    //printf("4.4\n");

    // on met à jour l'écran
    update_screen(renderer);
    //printf("4.5\n");

}

void apply_background(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite) {
    if (texture != NULL) {
        apply_texture(texture, renderer, (sprite->position.x), (sprite->position.y));
    }
}

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite) {
    if (texture != NULL) {
        apply_texture(texture, renderer, (sprite->position.x) - ((sprite->w) / 2),
                      (sprite->position.y) - ((sprite->h) / 2));
    }
}

void clean(SDL_Window *window, SDL_Renderer *renderer, resources_t *textures , world_t * world) {
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer, window);
}

void clean_textures(resources_t *textures) {
    clean_texture(textures->background);
    //clean_texture(textures->finish_line);
    clean_texture(textures->sprite);
    clean_texture(textures->zombie);
    clean_texture(textures->zombie_flipped);
    //clean_texture(textures->meteorites);
    //clean_font(textures->font);
    //clean_texture(textures->vies);

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