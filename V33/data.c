//
// Created by ludovic on 24/09/2021.
//


#include "data.h"
#include "graphics.h"
#include "liste.h"
#include "logic.h"
#include "colision.h"
#include <stdio.h>


void init_sprite_ptr(sprite_t *sprite, int x, int y, int w, int h, int v, nature_t nat) {
    sprite->position.x = x;
    sprite->position.y = y;
    sprite->h = h;
    sprite->w = w;
    sprite->disappear = 0;
    sprite->dir = 1;
    sprite->text_dir = 3;
    sprite->count = 0;
    sprite->speed = v;
    sprite->life = 1;
    sprite->nature = nat;
}


sprite_t init_sprite(sprite_t sprite, int x, int y, int w, int h, int v, nature_t nat) {
    sprite.position.x = x;
    sprite.position.y = y;
    sprite.h = h;
    sprite.w = w;
    sprite.disappear = 0;
    sprite.dir = 1;
    sprite.text_dir = 3;
    sprite.count = 0;
    sprite.speed = v;
    sprite.life = 1;
    sprite.nature = nat;
    return sprite;
}


void init_data(world_t *world) {

    srand(time(NULL));

    world->newgame = 1;
    world->nb_vies_restantes = NUMBER_LIFES;
    world->nb_faim_restant = NUMBER_LIFES;
    world->Car = l_vide();
    world->Zombie = l_vide();
    world->faim = l_vide();
    world->vies = l_vide();
    world->Gun = l_vide();
    world->Road = l_vide();
    world->tree = l_vide();
    //pas à la fin du jeu
    world->gameover = 0;
    world->c_s = false;
    world->bullet = l_vide();
    world->nb_bullets = 0;
    world->quit_menu = 0;
    world->mouse = init_sprite(world->mouse, (SCREEN_WIDTH) / 2, (SCREEN_HEIGHT) / 2, 1, 1, 1, Menu);
    world->nb_zombies_killed = 0;
    world->c_d = 0;
    world->Chicken = l_vide();


    world->Menu = init_sprite(world->Menu, (SCREEN_WIDTH) / 2,
                              (SCREEN_HEIGHT) / 2,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              1, Menu);

    world->play_menu = init_sprite(world->play_menu, 350, 100,
                                   200,
                                   100,
                                   1, Menu);

    world->new_game_menu = init_sprite(world->new_game_menu, 750, 100,
                                       200,
                                       100,
                                       1, Menu);

    world->settings_menu = init_sprite(world->settings_menu, 1150,
                                       100,
                                       200,
                                       100,
                                       1, Menu);

    world->exit_menu = init_sprite(world->exit_menu, 1550,
                                   100,
                                   200,
                                   100,
                                   1, Menu);


    //=======================================================================

    //initialise Terrain
    init_sprite_ptr(&world->Background,
                    0,
                    0,
                    GRASS_WIDTH,
                    GRASS_HEIGHT,
                    1,Background);

    init_sprite_ptr(&world->Rick, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, RICK_WIDTH, RICK_HEIGHT, 10,Rick);
    //=======================================================================

    for (int i = 0; i < NUMBER_ROADS; i++) {

        int x = 0;
        int y = i * 1000 - 1000 * NUMBER_ROADS / 2;

        sprite_t tmp_sprite;
        tmp_sprite = init_sprite(tmp_sprite, x, y, 1000, 1000, 1, Road);
        world->Road = ajouterEnFin(world->Road, tmp_sprite);
    }
    //=======================================================================
    for (int i = 0; i < NUMBER_ZOMBIES; i++) {

        int x = -(SCREEN_WIDTH * NUMBER_ZOMBIES / 50) + rand() % (SCREEN_WIDTH * NUMBER_ZOMBIES / 25);
        int y = -(SCREEN_WIDTH * NUMBER_ZOMBIES / 50) + rand() % (SCREEN_HEIGHT * NUMBER_ZOMBIES / 25);

        sprite_t tmp_sprite;
        tmp_sprite = init_sprite(tmp_sprite, x, y, 134, 180, 2, Zombie);
        world->Zombie = ajouterEnFin(world->Zombie, tmp_sprite);
    }

    //=======================================================================

    for (int i = 0; i < NUMBER_LIFES; i++) {

        sprite_t tmp_vies;
        sprite_t tmp_faim;
        tmp_vies = init_sprite(tmp_vies, SCREEN_WIDTH - (i + 1) * 32, 16, 32, 32, 0, Barre);
        tmp_faim = init_sprite(tmp_faim, SCREEN_WIDTH - (i + 1) * 32, 56, 32, 32, 0, Barre);
        world->vies = ajouterEnFin(world->vies, tmp_vies);
        world->faim = ajouterEnFin(world->faim, tmp_faim);
    }

    //=======================================================================

    for (int i = 0; i < NUMBER_GUNS; i++) {

        int x = rand() % SCREEN_WIDTH;
        int y = rand() % SCREEN_HEIGHT;

        sprite_t tmp_sprite;
        tmp_sprite = init_sprite(tmp_sprite, x, y, 90, 23, 1, Gun);
        world->Gun = ajouterEnFin(world->Gun, tmp_sprite);
    }

    //=======================================================================

    sprite_t tmp_sprite;
    int x, y;

    for (int i = 0; i < NUMBER_TREES; i++) {
        x = 600 + rand() % (SCREEN_WIDTH * 10);
        y = -(SCREEN_WIDTH * 40 + 10 * i) + rand() % (SCREEN_HEIGHT * 80 + 20 * i);
        tmp_sprite = init_sprite(tmp_sprite, x, y, 836, 1000, 1, Tree);
        world->tree = ajouterEnFin(world->tree, tmp_sprite);
    }

    //=======================================================================

    for (int i = 0; i < NUMBER_CARS; i++) {

        x = 0;
        y = -2 * SCREEN_HEIGHT + rand() % (4 * SCREEN_HEIGHT);

        int d = rand() % 4;

        if (d == 0 || d == 2) {
            tmp_sprite = init_sprite(tmp_sprite, x, y, 300, 540, 1, Car);
        } else if (d == 1 || d == 3) {
            tmp_sprite = init_sprite(tmp_sprite, x, y, 540, 300, 1, Car);
        }

        tmp_sprite.dir = d;
        tmp_sprite.text_dir = d;
        world->Car = ajouterEnFin(world->Car, tmp_sprite);
    }


    //=======================================================================

    for (int i = 0; i < NUMBER_CHICKEN; i++) {

        x = -(SCREEN_WIDTH * NUMBER_CHICKEN / 10) + rand() % (SCREEN_WIDTH * NUMBER_CHICKEN / 5);
        y = -(SCREEN_WIDTH * NUMBER_CHICKEN / 10) + rand() % (SCREEN_HEIGHT * NUMBER_CHICKEN / 5);

        sprite_t tmp_sprite;
        tmp_sprite = init_sprite(tmp_sprite, x, y, 140, 140, 3, Chicken);
        world->Chicken = ajouterEnFin(world->Chicken, tmp_sprite);
    }
}


void init_game(SDL_Window **window, SDL_Renderer **renderer, resources_t *textures, world_t *world) {
    init_ttf();
    init_sdl(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer, textures, world);
    init_audio();
}


void update_menu(world_t *world, resources_t *textures, SDL_Renderer *renderer) {

}


void update_data(world_t *world, resources_t *textures, SDL_Renderer *renderer) {
    move_zombies(world, textures, renderer);
    move_chicken(world, textures, renderer);
    move_bullets(world, textures, renderer);

    if(SDL_GetTicks() % 10000 > 9990 ){
        if(world->nb_faim_restant >= 1){
            world->nb_faim_restant --;
            if(world->nb_vies_restantes < NUMBER_LIFES){
                world->nb_vies_restantes ++;
            }
        }else{
            world->nb_vies_restantes--;
        }

    }
}


int is_game_over(world_t *world) {
    return world->gameover;
}


void print_sprite(sprite_t *sprite) {
    printf("Sprite: (x,y) = (%d,%d) ; (w,h) = (%d,%d)\n\n", sprite->position.x, sprite->position.y, sprite->w,
           sprite->h);
}


void print_position(position_t *position) {
    printf("Positiion: (x,y) = (%d,%d)\n\n", position->x, position->y);
}

void move_chicken(world_t *world, resources_t *textures, SDL_Renderer *renderer) {
    list_t tmp_chicken = world->Chicken;
    while (tmp_chicken != NULL) {
        if (distance(tmp_chicken->val, world->Rick) < 3 * SCREEN_HEIGHT) {
            if (tmp_chicken->val.life > 0) {
                move_sprite_randomly(tmp_chicken, textures, renderer);
            }
        }
        tmp_chicken = tmp_chicken->nxt;
    }
}

void move_all_except_rick(SDL_Event *event, world_t *world, SDL_Renderer *renderer, resources_t *textures) {

    list_t tmp_zombie = world->Zombie;
    list_t tmp_gun = world->Gun;
    list_t tmp_road = world->Road;
    list_t tmp_bullet = world->bullet;
    list_t tmp_tree = world->tree;
    list_t tmp_car = world->Car;
    list_t tmp_chicken = world->Chicken;
    sprite_t tmp_rick = world->Rick;
    int d = world->Rick.dir;


    if (d == 0) {
        tmp_rick.position.y -= RICK_STEP;
    } else if (d == 1) {
        tmp_rick.position.x += RICK_STEP;
    } else if (d == 2) {
        tmp_rick.position.y += RICK_STEP;
    } else if (d == 3) {
        tmp_rick.position.x -= RICK_STEP;
    }

    int flag = checkIllegalMove(world);

    if (flag == 0) {
        tmp_tree = world->tree;
        switch (d) {
            case 0:
                tmp_zombie = world->Zombie;
                while (tmp_zombie != NULL) {
                    tmp_zombie->val.position.y += world->Rick.speed;
                    if (tmp_zombie->val.life != 0 && (distance(tmp_zombie->val, world->Rick) < 400)) {
                        handle_Rick_Zombie_collision(world, &world->Rick, &tmp_zombie->val);
                    }
                    tmp_zombie = tmp_zombie->nxt;
                }
                tmp_gun = world->Gun;
                while (tmp_gun != NULL) {
                    tmp_gun->val.position.y += world->Rick.speed;
                    //handle_Rick_Weapon_collision(event, world, &world->Rick, &tmp_gun->val);
                    tmp_gun = tmp_gun->nxt;
                }
                tmp_road = world->Road;
                while (tmp_road != NULL) {
                    tmp_road->val.position.y += world->Rick.speed;
                    tmp_road = tmp_road->nxt;
                }
                tmp_bullet = world->bullet;
                while (tmp_bullet != NULL) {
                    tmp_bullet->val.position.y += world->Rick.speed;
                    tmp_bullet = tmp_bullet->nxt;
                }
                tmp_tree = world->tree;
                while (tmp_tree != NULL) {
                    tmp_tree->val.position.y += world->Rick.speed;
                    tmp_tree = tmp_tree->nxt;
                }
                tmp_car = world->Car;
                while (tmp_car != NULL) {
                    tmp_car->val.position.y += world->Rick.speed;
                    tmp_car = tmp_car->nxt;
                }
                tmp_chicken = world->Chicken;
                while (tmp_chicken != NULL) {
                    tmp_chicken->val.position.y += world->Rick.speed;
                    tmp_chicken = tmp_chicken->nxt;
                }
                world->Background.position.y += world->Rick.speed;

                break;
            case 1:
                tmp_zombie = world->Zombie;
                while (tmp_zombie != NULL) {
                    tmp_zombie->val.position.x -= world->Rick.speed;
                    if (tmp_zombie->val.life != 0 && (distance(tmp_zombie->val, world->Rick) < 400)) {
                        handle_Rick_Zombie_collision(world, &world->Rick, &tmp_zombie->val);
                    }
                    tmp_zombie = tmp_zombie->nxt;
                }
                tmp_gun = world->Gun;
                while (tmp_gun != NULL) {
                    tmp_gun->val.position.x -= world->Rick.speed;
                    //handle_Rick_Weapon_collision(event, world, &world->Rick, &tmp_gun->val);
                    tmp_gun = tmp_gun->nxt;
                }
                tmp_road = world->Road;
                while (tmp_road != NULL) {
                    tmp_road->val.position.x -= world->Rick.speed;
                    tmp_road = tmp_road->nxt;
                }
                tmp_bullet = world->bullet;
                while (tmp_bullet != NULL) {
                    tmp_bullet->val.position.x -= world->Rick.speed;
                    tmp_bullet = tmp_bullet->nxt;
                }
                tmp_tree = world->tree;
                while (tmp_tree != NULL) {
                    tmp_tree->val.position.x -= world->Rick.speed;
                    tmp_tree = tmp_tree->nxt;
                }
                tmp_car = world->Car;
                while (tmp_car != NULL) {
                    tmp_car->val.position.x -= world->Rick.speed;
                    tmp_car = tmp_car->nxt;
                }
                tmp_chicken = world->Chicken;
                while (tmp_chicken != NULL) {
                    tmp_chicken->val.position.x -= world->Rick.speed;
                    tmp_chicken = tmp_chicken->nxt;
                }
                world->Background.position.x -= world->Rick.speed;
                break;
            case 2:
                tmp_zombie = world->Zombie;
                while (tmp_zombie != NULL) {
                    tmp_zombie->val.position.y -= world->Rick.speed;
                    if (tmp_zombie->val.life != 0 && (distance(tmp_zombie->val, world->Rick) < 400)) {
                        handle_Rick_Zombie_collision(world, &world->Rick, &tmp_zombie->val);
                    }
                    tmp_zombie = tmp_zombie->nxt;
                }
                tmp_gun = world->Gun;
                while (tmp_gun != NULL) {
                    tmp_gun->val.position.y -= world->Rick.speed;
                    //handle_Rick_Weapon_collision(event, world, &world->Rick, &tmp_gun->val);
                    tmp_gun = tmp_gun->nxt;
                }
                tmp_road = world->Road;
                while (tmp_road != NULL) {
                    tmp_road->val.position.y -= world->Rick.speed;
                    tmp_road = tmp_road->nxt;
                }
                tmp_bullet = world->bullet;
                while (tmp_bullet != NULL) {
                    tmp_bullet->val.position.y -= world->Rick.speed;
                    tmp_bullet = tmp_bullet->nxt;
                }
                tmp_tree = world->tree;
                while (tmp_tree != NULL) {
                    tmp_tree->val.position.y -= world->Rick.speed;
                    tmp_tree = tmp_tree->nxt;
                }
                tmp_car = world->Car;
                while (tmp_car != NULL) {
                    tmp_car->val.position.y -= world->Rick.speed;
                    tmp_car = tmp_car->nxt;
                }
                tmp_chicken = world->Chicken;
                while (tmp_chicken != NULL) {
                    tmp_chicken->val.position.y -= world->Rick.speed;
                    tmp_chicken = tmp_chicken->nxt;
                }
                world->Background.position.y -= world->Rick.speed;
                break;
            case 3:
                tmp_zombie = world->Zombie;
                while (tmp_zombie != NULL) {
                    tmp_zombie->val.position.x += world->Rick.speed;
                    if (tmp_zombie->val.life != 0 && (distance(tmp_zombie->val, world->Rick) < 400)) {
                        handle_Rick_Zombie_collision(world, &world->Rick, &tmp_zombie->val);
                    }
                    tmp_zombie = tmp_zombie->nxt;
                }
                tmp_gun = world->Gun;
                while (tmp_gun != NULL) {
                    tmp_gun->val.position.x += world->Rick.speed;
                    //handle_Rick_Weapon_collision(event, world, &world->Rick, &tmp_gun->val);
                    tmp_gun = tmp_gun->nxt;
                }
                tmp_road = world->Road;
                while (tmp_road != NULL) {
                    tmp_road->val.position.x += world->Rick.speed;
                    tmp_road = tmp_road->nxt;
                }
                tmp_bullet = world->bullet;
                while (tmp_bullet != NULL) {
                    tmp_bullet->val.position.x += world->Rick.speed;
                    tmp_bullet = tmp_bullet->nxt;
                }
                tmp_tree = world->tree;
                while (tmp_tree != NULL) {
                    tmp_tree->val.position.x += world->Rick.speed;
                    tmp_tree = tmp_tree->nxt;
                }
                tmp_car = world->Car;
                while (tmp_car != NULL) {
                    tmp_car->val.position.x += world->Rick.speed;
                    tmp_car = tmp_car->nxt;
                }
                tmp_chicken = world->Chicken;
                while (tmp_chicken != NULL) {
                    tmp_chicken->val.position.x += world->Rick.speed;
                    tmp_chicken = tmp_chicken->nxt;
                }
                world->Background.position.x += world->Rick.speed;
                break;
        }
    } else { //flag == 1 <= IllegalMove

        tmp_tree = world->tree;
        world->Rick.speed *= 3;
        switch (d) {
            case 2:
                tmp_zombie = world->Zombie;
                while (tmp_zombie != NULL) {
                    tmp_zombie->val.position.y += world->Rick.speed;
                    if (tmp_zombie->val.life != 0 && (distance(tmp_zombie->val, world->Rick) < 400)) {
                        handle_Rick_Zombie_collision(world, &world->Rick, &tmp_zombie->val);
                    }
                    tmp_zombie = tmp_zombie->nxt;
                }
                tmp_gun = world->Gun;
                while (tmp_gun != NULL) {
                    tmp_gun->val.position.y += world->Rick.speed;
                    //handle_Rick_Weapon_collision(event, world, &world->Rick, &tmp_gun->val);
                    tmp_gun = tmp_gun->nxt;
                }
                tmp_road = world->Road;
                while (tmp_road != NULL) {
                    tmp_road->val.position.y += world->Rick.speed;
                    tmp_road = tmp_road->nxt;
                }
                tmp_bullet = world->bullet;
                while (tmp_bullet != NULL) {
                    tmp_bullet->val.position.y += world->Rick.speed;
                    tmp_bullet = tmp_bullet->nxt;
                }
                tmp_tree = world->tree;
                while (tmp_tree != NULL) {
                    tmp_tree->val.position.y += world->Rick.speed;
                    tmp_tree = tmp_tree->nxt;
                }
                tmp_car = world->Car;
                while (tmp_car != NULL) {
                    tmp_car->val.position.y += world->Rick.speed;
                    tmp_car = tmp_car->nxt;
                }
                tmp_chicken = world->Chicken;
                while (tmp_chicken != NULL) {
                    tmp_chicken->val.position.y += world->Rick.speed;
                    tmp_chicken = tmp_chicken->nxt;
                }
                world->Background.position.y += world->Rick.speed;

                break;
            case 3:
                tmp_zombie = world->Zombie;
                while (tmp_zombie != NULL) {
                    tmp_zombie->val.position.x -= world->Rick.speed;
                    if (tmp_zombie->val.life != 0 && (distance(tmp_zombie->val, world->Rick) < 400)) {
                        handle_Rick_Zombie_collision(world, &world->Rick, &tmp_zombie->val);
                    }
                    tmp_zombie = tmp_zombie->nxt;
                }
                tmp_gun = world->Gun;
                while (tmp_gun != NULL) {
                    tmp_gun->val.position.x -= world->Rick.speed;
                    //handle_Rick_Weapon_collision(event, world, &world->Rick, &tmp_gun->val);
                    tmp_gun = tmp_gun->nxt;
                }
                tmp_road = world->Road;
                while (tmp_road != NULL) {
                    tmp_road->val.position.x -= world->Rick.speed;
                    tmp_road = tmp_road->nxt;
                }
                tmp_bullet = world->bullet;
                while (tmp_bullet != NULL) {
                    tmp_bullet->val.position.x -= world->Rick.speed;
                    tmp_bullet = tmp_bullet->nxt;
                }
                tmp_tree = world->tree;
                while (tmp_tree != NULL) {
                    tmp_tree->val.position.x -= world->Rick.speed;
                    tmp_tree = tmp_tree->nxt;
                }
                tmp_car = world->Car;
                while (tmp_car != NULL) {
                    tmp_car->val.position.x -= world->Rick.speed;
                    tmp_car = tmp_car->nxt;
                }
                tmp_chicken = world->Chicken;
                while (tmp_chicken != NULL) {
                    tmp_chicken->val.position.x -= world->Rick.speed;
                    tmp_chicken = tmp_chicken->nxt;
                }
                world->Background.position.x -= world->Rick.speed;
                break;
            case 0:
                tmp_zombie = world->Zombie;
                while (tmp_zombie != NULL) {
                    tmp_zombie->val.position.y -= world->Rick.speed;
                    if (tmp_zombie->val.life != 0 && (distance(tmp_zombie->val, world->Rick) < 400)) {
                        handle_Rick_Zombie_collision(world, &world->Rick, &tmp_zombie->val);
                    }
                    tmp_zombie = tmp_zombie->nxt;
                }
                tmp_gun = world->Gun;
                while (tmp_gun != NULL) {
                    tmp_gun->val.position.y -= world->Rick.speed;
                    //handle_Rick_Weapon_collision(event, world, &world->Rick, &tmp_gun->val);
                    tmp_gun = tmp_gun->nxt;
                }
                tmp_road = world->Road;
                while (tmp_road != NULL) {
                    tmp_road->val.position.y -= world->Rick.speed;
                    tmp_road = tmp_road->nxt;
                }
                tmp_bullet = world->bullet;
                while (tmp_bullet != NULL) {
                    tmp_bullet->val.position.y -= world->Rick.speed;
                    tmp_bullet = tmp_bullet->nxt;
                }
                tmp_tree = world->tree;
                while (tmp_tree != NULL) {
                    tmp_tree->val.position.y -= world->Rick.speed;
                    tmp_tree = tmp_tree->nxt;
                }
                tmp_car = world->Car;
                while (tmp_car != NULL) {
                    tmp_car->val.position.y -= world->Rick.speed;
                    tmp_car = tmp_car->nxt;
                }
                tmp_chicken = world->Chicken;
                while (tmp_chicken != NULL) {
                    tmp_chicken->val.position.y -= world->Rick.speed;
                    tmp_chicken = tmp_chicken->nxt;
                }
                world->Background.position.y -= world->Rick.speed;
                break;
            case 1:
                tmp_zombie = world->Zombie;
                while (tmp_zombie != NULL) {
                    tmp_zombie->val.position.x += world->Rick.speed;
                    if (tmp_zombie->val.life != 0 && (distance(tmp_zombie->val, world->Rick) < 400)) {
                        handle_Rick_Zombie_collision(world, &world->Rick, &tmp_zombie->val);
                    }
                    tmp_zombie = tmp_zombie->nxt;
                }
                tmp_gun = world->Gun;
                while (tmp_gun != NULL) {
                    tmp_gun->val.position.x += world->Rick.speed;
                    //handle_Rick_Weapon_collision(event, world, &world->Rick, &tmp_gun->val);
                    tmp_gun = tmp_gun->nxt;
                }
                tmp_road = world->Road;
                while (tmp_road != NULL) {
                    tmp_road->val.position.x += world->Rick.speed;
                    tmp_road = tmp_road->nxt;
                }
                tmp_bullet = world->bullet;
                while (tmp_bullet != NULL) {
                    tmp_bullet->val.position.x += world->Rick.speed;
                    tmp_bullet = tmp_bullet->nxt;
                }
                tmp_tree = world->tree;
                while (tmp_tree != NULL) {
                    tmp_tree->val.position.x += world->Rick.speed;
                    tmp_tree = tmp_tree->nxt;
                }
                tmp_car = world->Car;
                while (tmp_car != NULL) {
                    tmp_car->val.position.x += world->Rick.speed;
                    tmp_car = tmp_car->nxt;
                }
                tmp_chicken = world->Chicken;
                while (tmp_chicken != NULL) {
                    tmp_chicken->val.position.x += world->Rick.speed;
                    tmp_chicken = tmp_chicken->nxt;
                }
                world->Background.position.x += world->Rick.speed;
                break;
        }
        world->Rick.speed /= 3;
    }

}


void move_zombies(world_t *world, resources_t *textures, SDL_Renderer *renderer) {
    list_t tmp_zombie = world->Zombie;
    while (tmp_zombie != NULL) {
        if (distance(tmp_zombie->val, world->Rick) < 3 * SCREEN_HEIGHT) {
            if (tmp_zombie->val.life > 0) {
                if (distance(tmp_zombie->val, world->Rick) < 600) {
                    move_zombie_towards_rick(tmp_zombie, world, textures, renderer);
                    if (tmp_zombie->val.life != 0) {
                        handle_Rick_Zombie_collision(world, &world->Rick, &tmp_zombie->val);
                    }
                } else {
                    move_sprite_randomly(tmp_zombie, textures, renderer);
                    if (tmp_zombie->val.life != 0) {
                        handle_Rick_Zombie_collision(world, &world->Rick, &tmp_zombie->val);
                    }
                }
            }
        }
        tmp_zombie = tmp_zombie->nxt;
    }
}


void move_zombie_towards_rick(list_t zombie, world_t *world, resources_t *textures, SDL_Renderer *renderer) {
    if (zombie->val.position.x < world->Rick.position.x) {
        if (zombie->val.position.y < world->Rick.position.y) {
            if (zombie->val.dir != 1) {
                zombie->val.dir = 1;
            } else {
                zombie->val.position.x += zombie->val.speed;
                zombie->val.position.y += zombie->val.speed;
            }
        } else if (zombie->val.position.y > world->Rick.position.y) {
            if (zombie->val.dir != 1) {
                zombie->val.dir = 1;
            } else {
                zombie->val.position.x += zombie->val.speed;
                zombie->val.position.y -= zombie->val.speed;
            }
        } else if (zombie->val.position.y == world->Rick.position.y) {
            if (zombie->val.dir != 1) {
                zombie->val.dir = 1;
            } else {
                zombie->val.position.x += zombie->val.speed;
            }
        }
    } else if (zombie->val.position.x > world->Rick.position.x) {
        if (zombie->val.position.y < world->Rick.position.y) {
            if (zombie->val.dir != 3) {
                zombie->val.dir = 3;
            } else {
                zombie->val.position.x -= zombie->val.speed;
                zombie->val.position.y += zombie->val.speed;
            }
        } else if (zombie->val.position.y > world->Rick.position.y) {
            if (zombie->val.dir != 3) {
                zombie->val.dir = 3;
            } else {
                zombie->val.position.x -= zombie->val.speed;
                zombie->val.position.y -= zombie->val.speed;
            }

        } else if (zombie->val.position.y == world->Rick.position.y) {
            if (zombie->val.dir != 3) {
                zombie->val.dir = 3;
            } else {
                zombie->val.position.x -= zombie->val.speed;
            }
        }
    } else if (zombie->val.position.x == world->Rick.position.x) {
        if (zombie->val.position.y < world->Rick.position.y) {
            zombie->val.position.y += zombie->val.speed;
        } else if (zombie->val.position.y > world->Rick.position.y) {
            zombie->val.position.y -= zombie->val.speed;
        } else {
            //world->gameover = 1;
        }
    }
}


void move_sprite_randomly(list_t sprite, resources_t *textures, SDL_Renderer *renderer) {
    int count_max = (rand() % 50) + 50;
    if (sprite->val.count < count_max) {
        switch (sprite->val.dir) {
            case 0:
                sprite->val.position.y -= sprite->val.speed;
                sprite->val.count++;
                break;
            case 1:
                sprite->val.position.x += sprite->val.speed;
                sprite->val.count++;
                break;
            case 2:
                sprite->val.position.y += sprite->val.speed;
                sprite->val.count++;
                break;
            case 3:
                sprite->val.position.x -= sprite->val.speed;
                sprite->val.count++;
                break;

        }
    } else {
        sprite->val.count = 0;
        sprite->val.dir = (rand() % (4));
        switch (sprite->val.dir) {
            case 0:
                sprite->val.position.y -= sprite->val.speed;
                sprite->val.count++;
                break;
            case 1:
                sprite->val.position.x += sprite->val.speed;
                sprite->val.count++;
                break;
            case 2:
                sprite->val.position.y += sprite->val.speed;
                sprite->val.count++;
                break;
            case 3:
                sprite->val.position.x -= sprite->val.speed;
                sprite->val.count++;
                break;

        }
    }
}


void clean_data(world_t *world) {
    for (int i = 0; i < NUMBER_ZOMBIES - 1; i++) {
        supprimerElementEnFin(world->Zombie);
    }
    for (int i = 0; i < NUMBER_LIFES - 1; i++) {
        supprimerElementEnFin(world->vies);
        supprimerElementEnFin(world->faim);
    }
    for (int i = 0; i < NUMBER_TREES - 1; i++) {
        supprimerElementEnFin(world->tree);
    }
    for (int i = 0; i < NUMBER_CARS - 1; i++) {
        supprimerElementEnFin(world->Car);
    }
    for (int i = 0; i < NUMBER_GUNS - 1; i++) {
        supprimerElementEnFin(world->Gun);
    }
    for (int i = 0; i < NUMBER_ROADS - 1; i++) {
        supprimerElementEnFin(world->Road);
    }
}


void move_bullets(world_t *world, resources_t *textures, SDL_Renderer *renderer) {
    list_t tmp_bullet = world->bullet;
    while (tmp_bullet != NULL) {
        if (distance(tmp_bullet->val, world->Rick) < 3 * SCREEN_HEIGHT) {
            if (tmp_bullet->val.dir == 3) {
                tmp_bullet->val.position.x -= tmp_bullet->val.speed;
                list_t tmp_zombie = world->Zombie;
                while (tmp_zombie != NULL) {
                    if (tmp_zombie->val.life != 0) {
                        handle_Bullet_Zombie_collision(world, &tmp_bullet->val, &tmp_zombie->val);
                    }
                    tmp_zombie = tmp_zombie->nxt;
                }
                list_t tmp_chicken = world->Chicken;
                while (tmp_chicken != NULL) {
                    if (tmp_chicken->val.life != 0) {
                        handle_Bullet_Chicken_collision(world, &tmp_bullet->val, &tmp_chicken->val);
                    }
                    tmp_chicken = tmp_chicken->nxt;
                }
            } else if (tmp_bullet->val.dir == 1) {
                tmp_bullet->val.position.x += tmp_bullet->val.speed;
                list_t tmp_zombie = world->Zombie;
                while (tmp_zombie != NULL) {
                    if (tmp_zombie->val.life != 0) {
                        handle_Bullet_Zombie_collision(world, &tmp_bullet->val, &tmp_zombie->val);
                    }
                    tmp_zombie = tmp_zombie->nxt;
                }
                list_t tmp_chicken = world->Chicken;
                while (tmp_chicken != NULL) {
                    if (tmp_chicken->val.life != 0) {
                        handle_Bullet_Chicken_collision(world, &tmp_bullet->val, &tmp_chicken->val);
                    }
                    tmp_chicken = tmp_chicken->nxt;
                }
            } else if (tmp_bullet->val.dir == 2) {
                tmp_bullet->val.position.y += tmp_bullet->val.speed;
                list_t tmp_zombie = world->Zombie;
                while (tmp_zombie != NULL) {
                    if (tmp_zombie->val.life != 0) {
                        handle_Bullet_Zombie_collision(world, &tmp_bullet->val, &tmp_zombie->val);
                    }
                    tmp_zombie = tmp_zombie->nxt;
                }
                list_t tmp_chicken = world->Chicken;
                while (tmp_chicken != NULL) {
                    if (tmp_chicken->val.life != 0) {
                        handle_Bullet_Chicken_collision(world, &tmp_bullet->val, &tmp_chicken->val);
                    }
                    tmp_chicken = tmp_chicken->nxt;
                }
            } else if (tmp_bullet->val.dir == 0) {
                tmp_bullet->val.position.y -= tmp_bullet->val.speed;
                list_t tmp_zombie = world->Zombie;
                while (tmp_zombie != NULL) {
                    if (tmp_zombie->val.life != 0) {
                        handle_Bullet_Zombie_collision(world, &tmp_bullet->val, &tmp_zombie->val);
                    }
                    tmp_zombie = tmp_zombie->nxt;
                }
                list_t tmp_chicken = world->Chicken;
                while (tmp_chicken != NULL) {
                    if (tmp_chicken->val.life != 0) {
                        handle_Bullet_Chicken_collision(world, &tmp_bullet->val, &tmp_chicken->val);
                    }
                    tmp_chicken = tmp_chicken->nxt;
                }
            }
        }


        //handle_Bullet_Zombie_collision(world, &world->Rick, &tmp_bullet->val);
        tmp_bullet = tmp_bullet->nxt;

    }
}
