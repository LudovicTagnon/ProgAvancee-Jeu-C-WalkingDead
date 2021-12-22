//
// Created by ludovic on 27/10/2021.
//

#ifndef V1_COLISION_H
#define V1_COLISION_H

#include "data.h"
#include "logic.h"

void handle_Rick_Car_collision(SDL_Event *event, world_t* world, resources_t *textures, SDL_Renderer *renderer, sprite_t* sp1, sprite_t* sp2);

void handle_Rick_Weapon_collision(SDL_Event *event, world_t* world, resources_t *textures, SDL_Renderer *renderer, sprite_t* sp1, sprite_t* sp2);

void handle_Rick_Food_collision(world_t *world, sprite_t *sp1, sprite_t *sp2);

void handle_Rick_Zombie_collision(world_t* world,sprite_t* sp1, sprite_t* sp2);


void handle_Bullet_Chicken_collision(world_t *world, sprite_t *sp1, sprite_t *sp2);

void handle_Bullet_Zombie_collision(world_t *world, sprite_t *sp1, sprite_t *sp2);

int checkIllegalMove(world_t *world);

#endif //V1_COLISION_H
