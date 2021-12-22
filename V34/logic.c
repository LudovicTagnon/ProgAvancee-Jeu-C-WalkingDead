//
// Created by ludovic on 27/10/2021.
//

#include "logic.h"
#include "graphics.h"
#include "liste.h"
#include <stdio.h>

double distance(sprite_t s1, sprite_t s2) {
    double s1x = s1.position.x;
    double s1y = s1.position.y;
    double s2x = s2.position.x;
    double s2y = s2.position.y;
    return (sqrt(pow(s1x - s2x, 2) + pow(s1y - s2y, 2)));
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

    return true;
}

