//
// Created by ludovic on 01/10/2021.
//
#include "constants.h"
#include "data.h"
#include "graphics.h"
#include "events.h"

#ifndef V1_AUDIO_H
#define V1_AUDIO_H

void prepare_audio(Mix_Chunk *_sample[NUM_WAVEFORMS]);

void clean_audio(Mix_Chunk *_sample[NUM_WAVEFORMS]);

#endif //V1_AUDIO_H
