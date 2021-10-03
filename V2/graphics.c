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
    textures->vies = charger_image_transparente("img/life.bmp",renderer);
}

void refresh_graphics(SDL_Renderer *renderer, world_t *world, resources_t *textures) {
    printf("4.0\n");

    //on vide le renderer
    clear_renderer(renderer); 
    printf("4.1\n");

    apply_terrain(renderer, world, textures);  
    printf("4.2\n");

    //application de la texture de Rick dans le renderer
    apply_sprite(renderer, textures->sprite, &world->Rick);
    printf("4.3\n");

    list_t tmp_zombie = world->Zombie;
    while(tmp_zombie!=NULL){
        if(tmp_zombie->val.dir==3){
            apply_sprite(renderer, textures->zombie_flipped, &tmp_zombie->val);
        }
        else if (tmp_zombie->val.dir==1){
            apply_sprite(renderer, textures->zombie, &tmp_zombie->val);
        }
        else{
            apply_sprite(renderer, textures->zombie, &tmp_zombie->val);
        }
        tmp_zombie = tmp_zombie->nxt;
    }

    list_t tmp_vie = world->vies;
    while(tmp_vie!=NULL){
        apply_sprite(renderer, textures->vies, &tmp_vie->val);
        tmp_vie = tmp_vie->nxt;
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
    clean_texture(textures->sprite);
    clean_texture(textures->zombie);
    clean_texture(textures->zombie_flipped);
    clean_texture(textures->vies);

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
