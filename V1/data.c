
#include "data.h"
#include "events.h"
#include "graphics.h"

void init(SDL_Window **window, SDL_Renderer **renderer, resources_t *textures, world_t *world) {
    init_sdl(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    //init_ttf();
    init_textures(*renderer, textures);
}

void init_sprite(sprite_t *sprite, int x, int y, int w, int h) {
    sprite->position.x = x;
    sprite->position.y = y;
    sprite->h = h;
    sprite->w = w;
    sprite->disappear = 0;
    sprite->dir = 1;
    sprite->count = 0;
}

void init_data(world_t *world) {

    //world->nb_zombies = NUMBER_ZOMBIES;

    //pas à la fin du jeu
    world->gameover = 0;

    //initialise Terrain
    init_sprite(&world->Background, (-GRASS_WIDTH * TERRAIN_SIZE) / 2, (-GRASS_HEIGHT * TERRAIN_SIZE) / 2, GRASS_WIDTH*TERRAIN_SIZE,
                GRASS_HEIGHT*TERRAIN_SIZE);

    //initialise vaisseau
    init_sprite(&world->Rick, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, RICK_WIDTH, RICK_HEIGHT);

    //initialise zombies
    for (int i = 0; i < NUMBER_ZOMBIES ; i++) {
        //int x = rand() % SCREEN_WIDTH; //SCREEN_WIDTH / 2 + 100 * i + 100
        //int y = rand() % SCREEN_HEIGHT;//SCREEN_HEIGHT / 2 + 100 * i + 100
        int x = rand() % SCREEN_WIDTH;
        int y = rand() % SCREEN_HEIGHT;
        init_sprite(&world->Zombie[i], x, y, 134, 180);
    }

    srand(time(NULL));
}

void init_lifes(world_t *world) {
    for (int i = 0; i < NUMBER_ZOMBIES; i++) {
        init_sprite(&world->vies[i], SCREEN_WIDTH - (i + 1) * LIFE_SIZE, 16, LIFE_SIZE, LIFE_SIZE);
    }
}

void update_data(world_t *world, resources_t *textures, SDL_Renderer *renderer){

    move_zombies(world, textures, renderer);

}

int is_game_over(world_t *world) {
    return world->gameover;
}


void print_sprite(sprite_t *sprite) {
    printf("Sprite: (x,y) = (%d,%d) ; (w,h) = (%d,%d)\n\n", sprite->position.x, sprite->position.y, sprite->w, sprite->h);
}

void print_position(position_t *position) {
    printf("Positiion: (x,y) = (%d,%d)\n\n", position->x, position->y);
}


void move_all_except_rick(world_t *world, int direction) {
    switch (direction) {
        case 0:
            world->Background.position.y += RICK_STEP;
            for (int i = 0; i < NUMBER_ZOMBIES; i++) {
                world->Zombie[i].position.y += RICK_STEP;
            }
            break;
        case 1:
            world->Background.position.x -= RICK_STEP;
            for (int i = 0; i < NUMBER_ZOMBIES; i++) {
                world->Zombie[i].position.x -= RICK_STEP;
            }
            break;
        case 2:
            world->Background.position.y -= RICK_STEP;
            for (int i = 0; i < NUMBER_ZOMBIES; i++) {
                world->Zombie[i].position.y -= RICK_STEP;
            }
            break;
        case 3:
            world->Background.position.x += RICK_STEP;
            for (int i = 0; i < NUMBER_ZOMBIES; i++) {
                world->Zombie[i].position.x += RICK_STEP;
            }
            break;

    }
}

void move_zombies(world_t *world, resources_t *textures, SDL_Renderer *renderer){
    for (int i = 0; i < NUMBER_ZOMBIES; i++) {
        if (distance(world->Zombie[i], world->Rick) < 600) {
        move_zombie_towards_rick(world, i, textures, renderer);
        } else {
        move_zombie_randomly(world, i, textures, renderer);
        }
    }

}


void move_zombie_towards_rick(world_t *world, int i, resources_t *textures, SDL_Renderer *renderer){
    if (world->Zombie[i].position.x < world->Rick.position.x) {
        if (world->Zombie[i].position.y < world->Rick.position.y) {
            if (world->Zombie[i].dir != 1) {
                world->Zombie[i].dir = 1;
            } else {
                world->Zombie[i].position.x += ZOMBIE_STEP;
                world->Zombie[i].position.y += ZOMBIE_STEP;
            }
        } else if (world->Zombie[i].position.y > world->Rick.position.y) {
            if (world->Zombie[i].dir != 1) {
                world->Zombie[i].dir = 1;
            } else {
                world->Zombie[i].position.x += ZOMBIE_STEP;
                world->Zombie[i].position.y -= ZOMBIE_STEP;
            }
        } else if (world->Zombie[i].position.y == world->Rick.position.y) {
            if (world->Zombie[i].dir != 1) {
                world->Zombie[i].dir = 1;
            } else {
                world->Zombie[i].position.x += ZOMBIE_STEP;
            }
        }
    }
    else if (world->Zombie[i].position.x > world->Rick.position.x) {
        if (world->Zombie[i].position.y < world->Rick.position.y) {
            if (world->Zombie[i].dir != 0) {
                world->Zombie[i].dir = 0;
            } else {
                world->Zombie[i].position.x -= ZOMBIE_STEP;
                world->Zombie[i].position.y += ZOMBIE_STEP;
            }
        } else if (world->Zombie[i].position.y > world->Rick.position.y) {
            if (world->Zombie[i].dir != 0) {
                world->Zombie[i].dir = 0;
            } else {
                world->Zombie[i].position.x -= ZOMBIE_STEP;
                world->Zombie[i].position.y -= ZOMBIE_STEP;
            }

        } else if (world->Zombie[i].position.y == world->Rick.position.y) {
            if (world->Zombie[i].dir != 0) {
                world->Zombie[i].dir = 0;
            } else {
                world->Zombie[i].position.x -= ZOMBIE_STEP;
            }
        }
    }
    else if (world->Zombie[i].position.x == world->Rick.position.x) {
        if (world->Zombie[i].position.y < world->Rick.position.y) {
            world->Zombie[i].position.y += ZOMBIE_STEP;
        } else if (world->Zombie[i].position.y > world->Rick.position.y) {
            world->Zombie[i].position.y -= ZOMBIE_STEP;
        } else {
            world->gameover = 1;
        }
    }
}

void move_zombie_randomly(world_t * world, int i, resources_t *textures, SDL_Renderer *renderer) {
    if (world->Zombie[i].count < 200 ) {
        switch (world->Zombie[i].dir) {
            case 0:
                world->Zombie[i].position.x -= ZOMBIE_STEP;
                world->Zombie[i].count++;
                break;
            case 1:
                world->Zombie[i].position.x += ZOMBIE_STEP;
                world->Zombie[i].count++;
                break;
            case 2:
                world->Zombie[i].position.y -= ZOMBIE_STEP;
                world->Zombie[i].count++;
                break;
            case 3:
                world->Zombie[i].position.y += ZOMBIE_STEP;
                world->Zombie[i].count++;
                break;

        }
    } else {
        world->Zombie[i].count = 0;
        world->Zombie[i].dir = (rand() % (4));
        switch (world->Zombie[i].dir) {
            case 0:
                world->Zombie[i].position.y -= ZOMBIE_STEP;
                world->Zombie[i].count++;
                break;
            case 1:
                world->Zombie[i].position.x += ZOMBIE_STEP;
                world->Zombie[i].count++;
                break;
            case 2:
                world->Zombie[i].position.y += ZOMBIE_STEP;
                world->Zombie[i].count++;
                break;
            case 3:
                world->Zombie[i].position.x -= ZOMBIE_STEP;
                world->Zombie[i].count++;
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

void clean_data(world_t * world){
    //free(world->Zombie);
    //free(world->vies);
    free(world);
}
