//
// Created by ludovic on 24/09/2021.
//

#ifndef V1_DATA_H
#define V1_DATA_H

#include "constants.h"


//-----------------------------------------------------------------------------------
// STRUCTURES //


struct position_s{
    int x;
    int y;
};
typedef struct position_s position_t;

struct sprite_s{
    position_t position;
    int h;
    int w;
    int disappear;
    int dir;
    int count;
    int speed;
};
typedef struct sprite_s sprite_t;


typedef struct element element;
struct element
{
    sprite_t val;
    struct element *nxt;
};

typedef element* list_t;


struct world_s{
    sprite_t Background;
    sprite_t Rick;
    //sprite_t mur;
    //sprite_t murs[NUMBER_OF_WALLS];
    list_t vies;
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu  */
    list_t Zombie ;
    int nb_vies_restantes;
};
typedef struct world_s world_t;



//-----------------------------------------------------------------------------------
// FONCTIONS //

void init(SDL_Window **window, SDL_Renderer ** renderer, resources_t *textures, world_t * world);

void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v);

void init_data(world_t * world);

void update_data(world_t *world, resources_t *textures, SDL_Renderer *renderer);

int is_game_over(world_t *world);

void handle_sprites_collision(world_t *world, sprite_t* sp1, sprite_t* sp2);

void print_sprite(sprite_t* sprite);

void print_position(position_t* position);

int sprites_collide(sprite_t* sp1, sprite_t* sp2);

void move_all_except_rick(world_t * world);

void move_zombies(world_t *world, resources_t *textures, SDL_Renderer *renderer);

void move_zombie_randomly(list_t zombie, resources_t *textures, SDL_Renderer *renderer);

void move_zombie_towards_rick(list_t zombie, world_t* world, resources_t *textures, SDL_Renderer *renderer);

double distance(sprite_t s1, sprite_t s2);

void clean_data(world_t * world);

#endif //V1_DATA_H
