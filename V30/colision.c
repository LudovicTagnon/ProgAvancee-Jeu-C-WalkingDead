//
// Created by ludovic on 27/10/2021.
//

#include "colision.h"
#include "liste.h"
#include <stdio.h>

void handle_Rick_Weapon_collision(SDL_Event *event, world_t *world, resources_t *textures, SDL_Renderer *renderer,
                                  sprite_t *sp1, sprite_t *sp2) {
    if (sprites_collide(sp1, sp2)) {
        world->c_s = true;
        sp2->disappear = 1;
    }
}

void handle_Rick_Car_collision(SDL_Event *event, world_t *world, resources_t *textures, SDL_Renderer *renderer,
                               sprite_t *sp1, sprite_t *sp2) {
    if (sprites_collide(sp1, sp2)) {
        world->c_d = true;
        sp2->disappear = 1;
        if (sp1->dir == 0) {
            sp1->w = 300;
            sp1->h = 540;
        } else if (sp1->dir == 1){
            sp1->h = 300;
            sp1->w = 540;
        }else if (sp1->dir == 2){
            sp1->w = 300;
            sp1->h = 540;
        }else if (sp1->dir == 3){
            sp1->h = 300;
            sp1->w = 540;
        }
        sp1->speed*=3;
        world->current_car = sp2;
    }
}

void handle_Rick_Zombie_collision(world_t *world, sprite_t *sp1, sprite_t *sp2) {
    //s1 : rick

    if (sprites_collide(sp1, sp2)) {

        int r = 100 + (rand() % 100);

        if(world->c_d==true){
            sp2->life--;
        }
        else if (world->nb_vies_restantes > 0) {
            if(world->c_d == false){
                world->nb_vies_restantes--;
            }
        }
        if (sp1->position.x <= sp2->position.x) {
            if (sp1->position.y <= sp2->position.y) {
                sp2->position.x += r;
                sp2->position.y += r;
            } else {
                sp2->position.x += r;
                sp2->position.y -= r;
            }
        } else {
            if (sp1->position.y <= sp2->position.y) {
                sp2->position.x -= r;
                sp2->position.y += r;
            } else {
                sp2->position.x += r;
                sp2->position.y -= r;
            }
        }

    }
}


void handle_Bullet_Zombie_collision(world_t *world, sprite_t *sp1, sprite_t *sp2) {
    //s1 : bullet

    if (sprites_collide(sp1, sp2)) {

        int recul = 100 + (rand() % 100);

        if (sp1->position.x <= sp2->position.x) {
            if (sp1->position.y <= sp2->position.y) {
                sp2->position.x += recul;
                //sp2->position.y += recul;
            } else {
                sp2->position.x += recul;
                //sp2->position.y -= recul;
            }
        } else {
            if (sp1->position.y <= sp2->position.y) {
                sp2->position.x -= recul;
                //sp2->position.y += recul;
            } else {
                sp2->position.x += recul;
                //sp2->position.y -= recul;
            }
        }
        if (sp2->life > 0) {
            sp2->life--;
            if(sp2->life==0){
                world->nb_zombies_killed++;
                sp2->count =0;
            }
            int tmp = 0;
            tmp = sp2->h;
            sp2->h = sp2->w;
            sp2->w = tmp;
            sp2->dir=sp1->dir;
            if(sp1->dir !=1){
                sp2->position.x -= sp2->w;
            }
        }
        sp1->position.x = 100000;
        sp1->position.y = 100000;
    }
}

int checkIllegalMove(world_t *world){

    int flag=0;

    list_t tmp_tree = world->tree;

    list_t tmp_car = world->Car;

    sprite_t tmp_tree_sprite;

    while ( tmp_tree != NULL && flag == 0 ) {

        tmp_tree_sprite = tmp_tree->val;
        tmp_tree_sprite.position.x -= 100;
        tmp_tree_sprite.position.y += 375;
        tmp_tree_sprite.w = 100;
        tmp_tree_sprite.h = -175;


        if (sprites_collide(&world->Rick, &tmp_tree_sprite)) {
            flag = 1;
        }
        if(sprites_collide(&world->Rick, &tmp_car->val) && world->c_d == 1 && tmp_car->val.disappear!=1){
            flag=1;
        }

        if(tmp_car->nxt != NULL){
            tmp_car = tmp_car->nxt;
        }
        tmp_tree = tmp_tree->nxt;
    }

    return flag;
}

void getCurrentTree(world_t *world){

    list_t tmp_tree = world->tree;
    while(tmp_tree != NULL){
        if (sprites_collide(&world->Rick, &tmp_tree->val)) {
            world->current_tree = &tmp_tree->val;
        }
        tmp_tree = tmp_tree->nxt;
    }

}