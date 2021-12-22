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

typedef enum {Rick, Zombie, Chicken, Tree, Road, Background, Bullet, Car, Gun, Barre, Menu} nature_t;

struct sprite_s{
    position_t position;
    int h;
    int w;
    int disappear;
    int dir;
    int text_dir;
    int count;
    int speed;
    int life;
    nature_t nature;
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
    sprite_t Menu;
    sprite_t play_menu;
    sprite_t new_game_menu;
    sprite_t settings_menu;
    sprite_t exit_menu;
    sprite_t Background;
    sprite_t Rick;
    list_t Car;
    list_t Gun;
    //sprite_t mur;
    //sprite_t murs[NUMBER_OF_WALLS];
    list_t vies;
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu  */
    list_t Zombie;
    list_t Road;
    int nb_vies_restantes;
    bool c_s;
    bool c_d;
    list_t bullet;
    list_t tree;
    int nb_bullets;
    bool quit_menu;
    sprite_t mouse;
    bool newgame;
    int nb_zombies_killed;
    sprite_t* current_car;
    list_t Chicken;
    list_t faim;
    int nb_faim_restant;
    int zoom;
    int time_debut_jeu;
    int time_mort;
    int rick_dead;
};
typedef struct world_s world_t;

//-----------------------------------------------------------------------------------
// FONCTIONS //

/*
void init_menu(SDL_Window **window, SDL_Renderer **renderer, resources_t *textures, world_t *world);
*/

void init_game(SDL_Window **window, SDL_Renderer ** renderer, resources_t *textures, world_t * world);

void init_sprite_ptr(sprite_t *sprite, int x, int y, int w, int h, int v, int life, nature_t nature);

sprite_t init_sprite(sprite_t sprite, int x, int y, int w, int h, int v, int life, nature_t nature);

void init_data(world_t * world);

void update_menu(world_t *world, resources_t *textures, SDL_Renderer *renderer);

void update_data(world_t *world, resources_t *textures, SDL_Renderer *renderer);

int is_game_over(world_t *world);

void handle_sprites_collision(world_t *world, sprite_t* sp1, sprite_t* sp2);

void print_sprite(sprite_t* sprite);

void print_position(position_t* position);

int sprites_collide(sprite_t* sp1, sprite_t* sp2);

void move_all_except_rick(SDL_Event *event, world_t *world, SDL_Renderer *renderer, resources_t *textures);

void move_chicken(world_t *world, resources_t *textures, SDL_Renderer *renderer);

void move_zombies(world_t *world, resources_t *textures, SDL_Renderer *renderer);

void move_sprite_randomly(list_t zombie, resources_t *textures, SDL_Renderer *renderer);

void move_zombie_towards_rick(list_t zombie, world_t* world, resources_t *textures, SDL_Renderer *renderer);

double distance(sprite_t s1, sprite_t s2);

void clean_data(world_t * world);

void handle_Rick_Car_collision(SDL_Event *event, world_t* world, resources_t *textures, SDL_Renderer *renderer, sprite_t* sp1, sprite_t* sp2);

void handle_Rick_Weapon_collision(SDL_Event *event, world_t* world, resources_t *textures, SDL_Renderer *renderer, sprite_t* sp1, sprite_t* sp2);

void handle_Rick_Zombie_collision(world_t* world,sprite_t* sp1, sprite_t* sp2);

void move_bullets(world_t *world, resources_t *textures, SDL_Renderer *renderer);

void handle_Bullet_Zombie_collision(world_t *world, sprite_t *sp1, sprite_t *sp2);

void writedata(FILE* file, world_t *world);

void loadgame(FILE* file, world_t *world);

#endif //V1_DATA_H
