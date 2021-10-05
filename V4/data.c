//
// Created by ludovic on 24/09/2021.
//


#include "data.h"
#include "events.h"
#include "graphics.h"
#include "liste.h"

void init(SDL_Window **window, SDL_Renderer **renderer, resources_t *textures, world_t *world) {
    init_sdl(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    //init_ttf();
    init_textures(*renderer, textures);
}

void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v) {
    sprite->position.x = x;
    sprite->position.y = y;
    sprite->h = h;
    sprite->w = w;
    sprite->disappear = 0;
    sprite->dir = 1;
    sprite->count = 0;
    sprite->speed = v;
}

void init_data(world_t *world) {

    world->Zombie = NULL;
    world->vies = NULL;
    world->Gun = NULL;
    world->Road = NULL;
    //pas à la fin du jeu
    world->gameover = 0;


    world->nb_vies_restantes = 3;
    printf("ERROR1\n");
    //initialise Terrain
    init_sprite(&world->Background,
                (-GRASS_WIDTH * TERRAIN_SIZE) / 2,
                (-GRASS_HEIGHT * TERRAIN_SIZE) / 2,
                GRASS_WIDTH * TERRAIN_SIZE,
                GRASS_HEIGHT * TERRAIN_SIZE,
                1);

    printf("ERROR2\n");
    //initialise vaisseau
    init_sprite(&world->Rick, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, RICK_WIDTH, RICK_HEIGHT, RICK_STEP);
    //=======================================================================

    for (int i = 0; i < NUMBER_ROADS; i++) {

        int x = 0;
        int y = i*1000 - 1000*NUMBER_ROADS/2;

        sprite_t tmp_sprite;
        sprite_t *p = &tmp_sprite;
        init_sprite(p, x, y, 1000, 1000, 1);
        world->Road = ajouterEnFin(world->Road, tmp_sprite);
    }

    //=======================================================================
    printf("ERROR3\n");
    //initialise zombies
    for (int i = 0; i < NUMBER_ZOMBIES; i++) {

        int x = rand() % SCREEN_WIDTH;
        int y = rand() % SCREEN_HEIGHT;

        sprite_t tmp_sprite;
        sprite_t *p = &tmp_sprite;
        init_sprite(p, x, y, 134, 180, 1);
        world->Zombie = ajouterEnFin(world->Zombie, tmp_sprite);
    }

    //=======================================================================

    for (int i = 0; i < NUMBER_LIFES; i++) {

        sprite_t tmp_sprite;
        sprite_t *p = &tmp_sprite;
        init_sprite(p, SCREEN_WIDTH - (i + 1) * 32, 16, 32, 32, 1);
        world->vies = ajouterEnFin(world->vies, tmp_sprite);
    }

    //=======================================================================

    for (int i = 0; i < NUMBER_GUNS; i++) {

        int x = rand() % SCREEN_WIDTH;
        int y = rand() % SCREEN_HEIGHT;

        sprite_t tmp_sprite;
        sprite_t *p = &tmp_sprite;
        init_sprite(p, x, y, 90, 23, 1);
        world->Gun = ajouterEnFin(world->Gun, tmp_sprite);
    }

    printf("ERROR5\n");

    srand(time(NULL));
}


void update_data(world_t *world, resources_t *textures, SDL_Renderer *renderer) {
    move_zombies(world, textures, renderer);
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


void move_all_except_rick(world_t *world) {
    list_t tmp_zombie;
    list_t tmp_gun;
    list_t tmp_road;
    int d = world->Rick.dir;
    switch (d) {
        case 0:
            tmp_zombie = world->Zombie;
            while (tmp_zombie != NULL) {
                tmp_zombie->val.position.y += world->Rick.speed;
                tmp_zombie = tmp_zombie->nxt;
            }
            tmp_gun = world->Gun;
            while (tmp_gun != NULL) {
                tmp_gun->val.position.y += world->Rick.speed;
                handle_Rick_Weapon_collision(world, &world->Rick, &tmp_gun->val);
                tmp_gun = tmp_gun->nxt;
            }
            tmp_road = world->Road;
            while (tmp_road != NULL) {
                tmp_road->val.position.y += world->Rick.speed;
                tmp_road = tmp_road->nxt;
            }
            world->Background.position.y += world->Rick.speed;
            break;
        case 1:
            tmp_zombie = world->Zombie;
            while (tmp_zombie != NULL) {
                tmp_zombie->val.position.x -= world->Rick.speed;
                tmp_zombie = tmp_zombie->nxt;
            }
            tmp_gun = world->Gun;
            while (tmp_gun != NULL) {
                tmp_gun->val.position.x -= world->Rick.speed;
                handle_Rick_Weapon_collision(world, &world->Rick, &tmp_gun->val);
                tmp_gun = tmp_gun->nxt;
            }
            tmp_road = world->Road;
            while (tmp_road != NULL) {
                tmp_road->val.position.x -= world->Rick.speed;
                tmp_road = tmp_road->nxt;
            }
            world->Background.position.x -= world->Rick.speed;
            break;
        case 2:
            tmp_zombie = world->Zombie;
            while (tmp_zombie != NULL) {
                tmp_zombie->val.position.y -= world->Rick.speed;
                tmp_zombie = tmp_zombie->nxt;
            }
            tmp_gun = world->Gun;
            while (tmp_gun != NULL) {
                tmp_gun->val.position.y -= world->Rick.speed;
                handle_Rick_Weapon_collision(world, &world->Rick, &tmp_gun->val);
                tmp_gun = tmp_gun->nxt;
            }
            tmp_road = world->Road;
            while (tmp_road != NULL) {
                tmp_road->val.position.y -= world->Rick.speed;
                tmp_road = tmp_road->nxt;
            }
            world->Background.position.y -= world->Rick.speed;
            break;
        case 3:
            tmp_zombie = world->Zombie;
            while (tmp_zombie != NULL) {
                tmp_zombie->val.position.x += world->Rick.speed;
                tmp_zombie = tmp_zombie->nxt;
            }
            tmp_gun = world->Gun;
            while (tmp_gun != NULL) {
                tmp_gun->val.position.x += world->Rick.speed;
                handle_Rick_Weapon_collision(world, &world->Rick, &tmp_gun->val);
                tmp_gun = tmp_gun->nxt;
            }
            tmp_road = world->Road;
            while (tmp_road != NULL) {
                tmp_road->val.position.x += world->Rick.speed;
                tmp_road = tmp_road->nxt;
            }
            world->Background.position.x += world->Rick.speed;
            break;
    }
    free(tmp_zombie);
}


void move_zombies(world_t *world, resources_t *textures, SDL_Renderer *renderer) {

    list_t tmp_zombie = world->Zombie;
    while (tmp_zombie != NULL) {
        if (distance(tmp_zombie->val, world->Rick) < 600) {
            move_zombie_towards_rick(tmp_zombie, world, textures, renderer);
        } else {
            move_zombie_randomly(tmp_zombie, textures, renderer);
        }
        tmp_zombie = tmp_zombie->nxt;
    }
    free(tmp_zombie);
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
            world->gameover = 1;
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
    for (int i = 0; i < NUMBER_ZOMBIES-1; i++) {
        supprimerElementEnFin(world->Zombie);
    }
    for (int i = 0; i < NUMBER_ZOMBIES-1; i++) {
        supprimerElementEnFin(world->vies);
    }
}

int sprites_collide(sprite_t* sp1, sprite_t* sp2){

    sprite_t s1 = *sp1;

    sprite_t s2 = *sp2;

    if( ( ( ( s1.position.x - s1.w/2 <= s2.position.x + s2.w/2 )&&( s2.position.x + s2.w/2 <= s1.position.x + s1.w/2 ) ) || ( ( s1.position.x - s1.w/2 <= s2.position.x - s2.w/2 )&&( s2.position.x - s2.w/2 <= s1.position.x + s1.w/2 ) ) )
        && ( ( ( ( s1.position.y - s1.h/2 <= s2.position.y + s2.h/2 )&&( s2.position.y + s2.h/2 <= s1.position.y + s1.h/2 ) ) || ( ( s1.position.y - s1.h/2 <= s2.position.y - s2.h/2 )&&( s2.position.y - s2.h/2 <= s1.position.y + s1.h/2 ) ) ) ) ){
        return 1;
    }

    return 0;
}

void handle_Rick_Weapon_collision(world_t* world,sprite_t* sp1, sprite_t* sp2) {
    if(sprites_collide( sp1 , sp2 )){
        sp2->disappear=1;
        //sp1->canshoot=1;
    }
}




















