//
// Created by ludovic on 27/10/2021.
//

#ifndef V1_SAVING_H
#define V1_SAVING_H

#include "data.h"

void writedata(FILE* file, world_t *world);

void loadgame(FILE* file, world_t *world);


#endif //V1_SAVING_H
