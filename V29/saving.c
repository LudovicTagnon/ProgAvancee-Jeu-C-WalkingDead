//
// Created by ludovic on 27/10/2021.
//

#include "saving.h"
#include "liste.h"
#include <stdio.h>


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