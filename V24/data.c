//
// Created by ludovic on 24/09/2021.
//


#include "data.h"
#include "graphics.h"
#include "liste.h"
#include <stdio.h>


void init_sprite_ptr(sprite_t *sprite, int x, int y, int w, int h, int v) {
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
}


sprite_t init_sprite(sprite_t sprite, int x, int y, int w, int h, int v) {
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
    return sprite;
}


void init_data(world_t *world) {

    srand(time(NULL));

    world->newgame = 1;
    world->nb_vies_restantes = NUMBER_LIFES;
    world->Car = l_vide();
    world->Zombie = l_vide();
    world->vies = l_vide();
    world->Gun = l_vide();
    world->Road = l_vide();
    //pas à la fin du jeu
    world->gameover = 0;
    world->c_s = false;
    world->bullet = l_vide();
    world->nb_bullets = 0;
    world->quit_menu = 0;
    world->mouse = init_sprite(world->mouse, (SCREEN_WIDTH) / 2, (SCREEN_HEIGHT) / 2, 1, 1, 1);
    world->nb_zombies_killed = 0;
    world->c_d =0;


    world->Menu = init_sprite(world->Menu, (SCREEN_WIDTH) / 2,
                              (SCREEN_HEIGHT) / 2,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              1);

    world->play_menu = init_sprite(world->play_menu, 350, 100,
                                   200,
                                   100,
                                   1);

    world->new_game_menu = init_sprite(world->new_game_menu, 750, 100,
                                       200,
                                       100,
                                       1);

    world->settings_menu = init_sprite(world->settings_menu, 1150,
                                       100,
                                       200,
                                       100,
                                       1);

    world->exit_menu = init_sprite(world->exit_menu, 1550,
                                   100,
                                   200,
                                   100,
                                   1);


    //=======================================================================

    //initialise Terrain
    init_sprite_ptr(&world->Background,
                    0,
                    0,
                    GRASS_WIDTH,
                    GRASS_HEIGHT,
                    1);

    init_sprite_ptr(&world->Rick, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, RICK_WIDTH, RICK_HEIGHT, 10);
    //=======================================================================

    for (int i = 0; i < NUMBER_ROADS ; i++) {

        int x = 0;
        int y = i * 1000 - 1000 * NUMBER_ROADS / 2;

        sprite_t tmp_sprite;
        tmp_sprite = init_sprite(tmp_sprite, x, y, 1000, 1000, 1);
        world->Road = ajouterEnFin(world->Road, tmp_sprite);
    }
    //=======================================================================
    for (int i = 0; i < NUMBER_ZOMBIES ; i++) {

        int x = -(SCREEN_WIDTH * NUMBER_ZOMBIES / 50) + rand() % (SCREEN_WIDTH * NUMBER_ZOMBIES / 25);
        int y = -(SCREEN_WIDTH * NUMBER_ZOMBIES / 50) + rand() % (SCREEN_HEIGHT * NUMBER_ZOMBIES / 25);

        sprite_t tmp_sprite;
        tmp_sprite = init_sprite(tmp_sprite, x, y, 134, 180, 1);
        world->Zombie = ajouterEnFin(world->Zombie, tmp_sprite);
    }

    //=======================================================================

    for (int i = 0; i < NUMBER_LIFES ; i++) {

        sprite_t tmp_sprite;
        tmp_sprite = init_sprite(tmp_sprite, SCREEN_WIDTH - (i + 1) * 32, 16, 32, 32, 1);
        world->vies = ajouterEnFin(world->vies, tmp_sprite);
    }

    //=======================================================================

    for (int i = 0; i < NUMBER_GUNS ; i++) {

        int x = rand() % SCREEN_WIDTH;
        int y = rand() % SCREEN_HEIGHT;

        sprite_t tmp_sprite;
        tmp_sprite = init_sprite(tmp_sprite, x, y, 90, 23, 1);
        world->Gun = ajouterEnFin(world->Gun, tmp_sprite);
    }

    //=======================================================================

    sprite_t tmp_sprite;
    int x, y;

    for (int i = 0; i < NUMBER_TREES ; i++) {
        x = 600 + rand() % (SCREEN_WIDTH * 20);
        y = -(SCREEN_WIDTH * 40 + 50*i) + rand() % (SCREEN_HEIGHT * 80 + 100*i);
        tmp_sprite = init_sprite(tmp_sprite, x, y, 1000, 1000, 1);
        world->tree = ajouterEnFin(world->tree, tmp_sprite);
    }

    //=======================================================================

    for (int i = 0; i < NUMBER_CARS ; i++) {

        x = - (400 + rand() % (4*SCREEN_WIDTH));
        y = -2*SCREEN_HEIGHT + rand() % (4*SCREEN_HEIGHT);

        int d = rand() % 4;

        if(d==0 || d==2){
            tmp_sprite = init_sprite(tmp_sprite, x, y, 300, 540, 1);
        }else if(d==1 || d==3){
            tmp_sprite = init_sprite(tmp_sprite, x, y, 540, 300, 1);
        }

        tmp_sprite.dir = d;
        tmp_sprite.text_dir = d;
        world->Car = ajouterEnFin(world->Car, tmp_sprite);
    }

    //=======================================================================

    world->current_tree = &world->tree->val;

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
    move_bullets(world, textures, renderer);
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


void move_all_except_rick(SDL_Event *event, world_t *world, SDL_Renderer *renderer, resources_t *textures) {
    list_t tmp_zombie = world->Zombie;
    list_t tmp_gun = world->Gun;
    list_t tmp_road = world->Road;
    list_t tmp_bullet = world->bullet;
    list_t tmp_tree = world->tree;
    list_t tmp_car = world->Car;
    sprite_t tmp_rick = world->Rick;
    int d = world->Rick.dir;

    if(distance(world->Background, world->Rick) > (1.5*SCREEN_WIDTH) ){
        world->Background.position.x = 0;
        world->Background.position.y = 0;
    }


    if (d == 0) {
        tmp_rick.position.y -= RICK_STEP;
    } else if (d == 1) {
        tmp_rick.position.x += RICK_STEP;
    } else if (d == 2) {
        tmp_rick.position.y += RICK_STEP;
    } else if (d == 3) {
        tmp_rick.position.x -= RICK_STEP;
    }

    int flag = 0;
    sprite_t tmp_tree_sprite;
    while (tmp_tree != NULL && flag == 0) {
        tmp_tree_sprite = tmp_tree->val;
        tmp_tree_sprite.position.x -= 100;
        tmp_tree_sprite.position.y += 375;
        tmp_tree_sprite.w = 100;
        tmp_tree_sprite.h = -175;
        if (sprites_collide(&tmp_rick, &tmp_tree_sprite)) {
            flag = 1;
        }
        if (sprites_collide(&tmp_rick, &tmp_tree->val)) {
            world->current_tree = &tmp_tree->val;
        }

        tmp_tree = tmp_tree->nxt;
    }
    tmp_tree = world->tree;

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
                world->Background.position.x += world->Rick.speed;
                break;
        }
    } else {
        tmp_tree = world->tree;
        world->Rick.speed /= 10;
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
                world->Background.position.x += world->Rick.speed;
                break;
        }
        world->Rick.speed *= 10;
    }

    free(tmp_car);
    free(tmp_zombie);
    free(tmp_gun);
    free(tmp_road);
    free(tmp_bullet);
    free(tmp_tree);
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
                    move_zombie_randomly(tmp_zombie, textures, renderer);
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


void move_zombie_randomly(list_t zombie, resources_t *textures, SDL_Renderer *renderer) {
    if (zombie->val.count < 50) {
        switch (zombie->val.dir) {
            case 0:
                zombie->val.position.y -= zombie->val.speed;
                zombie->val.count++;
                break;
            case 1:
                zombie->val.position.x += zombie->val.speed;
                zombie->val.count++;
                break;
            case 2:
                zombie->val.position.y += zombie->val.speed;
                zombie->val.count++;
                break;
            case 3:
                zombie->val.position.x -= zombie->val.speed;
                zombie->val.count++;
                break;

        }
    } else {
        zombie->val.count = 0;
        zombie->val.dir = (rand() % (4));
        switch (zombie->val.dir) {
            case 0:
                zombie->val.position.y -= zombie->val.speed;
                zombie->val.count++;
                break;
            case 1:
                zombie->val.position.x += zombie->val.speed;
                zombie->val.count++;
                break;
            case 2:
                zombie->val.position.y += zombie->val.speed;
                zombie->val.count++;
                break;
            case 3:
                zombie->val.position.x -= zombie->val.speed;
                zombie->val.count++;
                break;

        }
    }
}


double distance(sprite_t s1, sprite_t s2) {
    double s1x = s1.position.x;
    double s1y = s1.position.y;
    double s2x = s2.position.x;
    double s2y = s2.position.y;
    return (sqrt(pow(s1x - s2x, 2) + pow(s1y - s2y, 2)));
}


void clean_data(world_t *world) {
    for (int i = 0; i < NUMBER_ZOMBIES - 1; i++) {
        supprimerElementEnFin(world->Zombie);
    }
    for (int i = 0; i < NUMBER_LIFES - 1; i++) {
        supprimerElementEnFin(world->vies);
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


int sprites_collide(sprite_t *sp1, sprite_t *sp2) {

    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

    //Calcul les cotes du rectangle A
    left1 = sp1->position.x - (sp1->w) / 2;
    right1 = sp1->position.x + (sp1->w) / 2;
    top1 = sp1->position.y - (sp1->h) / 2;
    bottom1 = sp1->position.y + (sp1->h) / 2;

    //Calcul les cotes du rectangle B
    left2 = sp2->position.x - (sp2->w) / 2;
    right2 = sp2->position.x + (sp2->w) / 2;
    top2 = sp2->position.y - (sp2->h) / 2;
    bottom2 = sp2->position.y + (sp2->h) / 2;

    if (bottom1 <= top2) {
        return false;
    }

    if (top1 >= bottom2) {
        return false;
    }

    if (right1 <= left2) {
        return false;
    }

    if (left1 >= right2) {
        return false;
    }

    //printf("COLLISION\n");
    return true;
}


void handle_Rick_Weapon_collision(SDL_Event *event, world_t *world, resources_t *textures, SDL_Renderer *renderer,
                                  sprite_t *sp1, sprite_t *sp2) {
    if (sprites_collide(sp1, sp2)) {
        world->c_s = true;
        sp2->disappear = 1;
        if (sp1->dir == 1) {
            textures->sprite = charger_image_transparente("img/rick_gun_flipped.bmp", renderer);
        } else {
            textures->sprite = charger_image_transparente("img/rick_gun.bmp", renderer);
        }
    }
}

void handle_Rick_Car_collision(SDL_Event *event, world_t *world, resources_t *textures, SDL_Renderer *renderer,
                                  sprite_t *sp1, sprite_t *sp2) {
    if (sprites_collide(sp1, sp2)) {
        world->c_d = true;
        sp2->disappear = 1;
        if (sp1->dir == 0) {
            textures->sprite = charger_image_transparente("img/car_up.bmp", renderer);
            sp1->w = 300;
            sp1->h = 540;
        } else if (sp1->dir == 1){
            textures->sprite = charger_image_transparente("img/car_right.bmp", renderer);
            sp1->h = 300;
            sp1->w = 540;
        }else if (sp1->dir == 2){
            textures->sprite = charger_image_transparente("img/car_down.bmp", renderer);
            sp1->w = 300;
            sp1->h = 540;
        }else if (sp1->dir == 3){
            textures->sprite = charger_image_transparente("img/car_left.bmp", renderer);
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


void move_bullets(world_t *world, resources_t *textures, SDL_Renderer *renderer) {
    list_t tmp_bullet = world->bullet;
    while (tmp_bullet!= NULL){
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
            } else if (tmp_bullet->val.dir == 1) {
                tmp_bullet->val.position.x += tmp_bullet->val.speed;
                list_t tmp_zombie = world->Zombie;
                while (tmp_zombie != NULL) {
                    if (tmp_zombie->val.life != 0) {
                        handle_Bullet_Zombie_collision(world, &tmp_bullet->val, &tmp_zombie->val);
                    }
                    tmp_zombie = tmp_zombie->nxt;
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
            } else if (tmp_bullet->val.dir == 0) {
                tmp_bullet->val.position.y -= tmp_bullet->val.speed;
                list_t tmp_zombie = world->Zombie;
                while (tmp_zombie != NULL) {
                    if (tmp_zombie->val.life != 0) {
                        handle_Bullet_Zombie_collision(world, &tmp_bullet->val, &tmp_zombie->val);
                    }
                    tmp_zombie = tmp_zombie->nxt;
                }
            }
        }


        //handle_Bullet_Zombie_collision(world, &world->Rick, &tmp_bullet->val);
        tmp_bullet = tmp_bullet->nxt;

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
            world->nb_zombies_killed++;
            int tmp = 0;
            tmp = sp2->h;
            sp2->h = sp2->w;
            sp2->w = tmp;
        }
        sp1->position.x = 100000;
        sp1->position.y = 100000;
    }
}


void writedata(FILE *file, world_t *world) {

    file = fopen("Save.txt","w");
    if(file == NULL)
    {
        printf("Error!");
        exit(1);
    }

    sprite_t sp;
    sp = world->Rick;

    fprintf(file, "%d,%d,%d,%d,%d,%d,%d,%d,%d,", sp.position.x, sp.position.y, sp.speed, sp.dir, sp.life, sp.h, sp.w,
            sp.disappear, sp.text_dir);

    sp = world->Background;
    fprintf(file, "%d,%d,%d,%d,%d,%d,%d,%d,%d,", sp.position.x, sp.position.y, sp.speed, sp.dir, sp.life, sp.h, sp.w,
            sp.disappear, sp.text_dir);

    list_t tmp = world->Zombie;
    while (tmp != NULL) {
        sp = tmp->val;
        fprintf(file, "%d,%d,%d,%d,%d,%d,%d,%d,%d,", sp.position.x, sp.position.y, sp.speed, sp.dir, sp.life, sp.h,
                sp.w, sp.disappear, sp.text_dir);
        tmp = tmp->nxt;
    }

    tmp = world->Road;
    while (tmp != NULL) {
        sp = tmp->val;
        fprintf(file, "%d,%d,%d,%d,%d,%d,%d,%d,%d,", sp.position.x, sp.position.y, sp.speed, sp.dir, sp.life, sp.h,
                sp.w, sp.disappear, sp.text_dir);
        tmp = tmp->nxt;
    }

    tmp = world->Gun;
    while (tmp != NULL) {
        sp = tmp->val;
        fprintf(file, "%d,%d,%d,%d,%d,%d,%d,%d,%d,", sp.position.x, sp.position.y, sp.speed, sp.dir, sp.life, sp.h,
                sp.w, sp.disappear, sp.text_dir);
        tmp = tmp->nxt;
    }

    tmp = world->vies;
    while (tmp != NULL) {
        sp = tmp->val;
        fprintf(file, "%d,%d,%d,%d,%d,%d,%d,%d,%d,", sp.position.x, sp.position.y, sp.speed, sp.dir, sp.life, sp.h,
                sp.w, sp.disappear, sp.text_dir);
        tmp = tmp->nxt;
    }

    fprintf(file, "%d,%d,%d", world->nb_vies_restantes, world->c_s, world->nb_zombies_killed);


    fclose(file);

}


void loadgame(FILE *file, world_t *world) {

    file = fopen("Save.txt","r");
    if(file == NULL)
    {
        printf("Error!");
        exit(1);
    }

    printf("1\n");
    int t[20000];
    int n, i;
    char *token;
    char help[20000];
    fscanf(file, "%s", help);
    token = strtok(help, ",");
    i = 0;
    while (token != NULL) {
        t[i] = atoi(token);
        token = strtok(NULL, ",");
        i++;
    }
    n = i;

    for (int j = 0; j < n; j++) {
        printf("%i: %d ", j, t[j]);
    }

    sprite_t *sp = &world->Rick;
    for (int m = 0; m < 2; m++) {
        sp->position.x = t[0 + m * 9];
        sp->position.y = t[1 + m * 9];
        sp->speed = t[2 + m * 9];
        sp->dir = t[3 + m * 9];
        sp->life = t[4 + m * 9];
        sp->h = t[5 + m * 9];
        sp->w = t[6 + m * 9];
        sp->disappear = t[7 + m * 9];
        sp->text_dir = t[8 + m * 9];
        sp = &world->Background;
    }

    int m = 2;
    list_t tmp = world->Zombie;
    while (tmp != NULL) {
        sp = &tmp->val;
        sp->position.x = t[0 + m * 9];
        sp->position.y = t[1 + m * 9];
        sp->speed = t[2 + m * 9];
        sp->dir = t[3 + m * 9];
        sp->life = t[4 + m * 9];
        sp->h = t[5 + m * 9];
        sp->w = t[6 + m * 9];
        sp->disappear = t[7 + m * 9];
        sp->text_dir = t[8 + m * 9];

        tmp = tmp->nxt;
        m++;
    }

    tmp = world->Road;
    while (tmp != NULL) {
        sp = &tmp->val;
        sp->position.x = t[0 + m * 9];
        sp->position.y = t[1 + m * 9];
        sp->speed = t[2 + m * 9];
        sp->dir = t[3 + m * 9];
        sp->life = t[4 + m * 9];
        sp->h = t[5 + m * 9];
        sp->w = t[6 + m * 9];
        sp->disappear = t[7 + m * 9];
        sp->text_dir = t[8 + m * 9];

        tmp = tmp->nxt;
        m++;
    }

    tmp = world->Gun;
    while (tmp != NULL) {
        sp = &tmp->val;
        sp->position.x = t[0 + m * 9];
        sp->position.y = t[1 + m * 9];
        sp->speed = t[2 + m * 9];
        sp->dir = t[3 + m * 9];
        sp->life = t[4 + m * 9];
        sp->h = t[5 + m * 9];
        sp->w = t[6 + m * 9];
        sp->disappear = t[7 + m * 9];
        sp->text_dir = t[8 + m * 9];

        tmp = tmp->nxt;
        m++;
    }


    tmp = world->vies;
    while (tmp != NULL) {
        sp = &tmp->val;
        sp->position.x = t[0 + m * 9];
        sp->position.y = t[1 + m * 9];
        sp->speed = t[2 + m * 9];
        sp->dir = t[3 + m * 9];
        sp->life = t[4 + m * 9];
        sp->h = t[5 + m * 9];
        sp->w = t[6 + m * 9];
        sp->disappear = t[7 + m * 9];
        sp->text_dir = t[8 + m * 9];

        tmp = tmp->nxt;
        m++;
    }

    world->nb_vies_restantes = t[0 + m * 9];
    world->c_s = t[1 + m * 9];
    world->nb_zombies_killed = t[2 + m * 9];
    printf("%i\n", 1 + m * 9);

    fclose(file);

}





