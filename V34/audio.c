//
// Created by ludovic on 01/10/2021.
//

#include "audio.h"

void prepare_audio(Mix_Chunk *_sample[NUM_WAVEFORMS]){
    const char *_waveFileNames[] =
            {
                    "wav/shotgun.wav",
                    "wav/theme.wav",
            };

    memset(_sample, 0, sizeof(Mix_Chunk *) * 2);

    // Set up the audio stream
    int result = Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
    if (result < 0) {
        fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());

    }

    result = Mix_AllocateChannels(4);
    if (result < 0) {
        fprintf(stderr, "Unable to allocate mixing channels: %s\n", SDL_GetError());

    }

    // Load waveforms
    for (int i = 0; i < NUM_WAVEFORMS; i++) {
        _sample[i] = Mix_LoadWAV(_waveFileNames[i]);
        if (_sample[i] == NULL) {
            fprintf(stderr, "Unable to load wave file: %s\n", _waveFileNames[i]);
        }
    }
}

void clean_audio(Mix_Chunk *_sample[NUM_WAVEFORMS]){
    for( int i = 0; i < NUM_WAVEFORMS; i++ )
    {
        Mix_FreeChunk(_sample[i]);
    }
    Mix_CloseAudio();
}

Mix_Music * init_music(Mix_Music *musique){
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
        printf("%s", Mix_GetError());
    }
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
    musique = Mix_LoadMUS("mp3/theme.mp3");
    return musique;
}

void launch_music(Mix_Music * musique){
    Mix_PlayMusic(musique, -1);
}

void play_pause_music(){
    if(Mix_PausedMusic() == 1)//Si la musique est en pause
    {
        Mix_ResumeMusic(); //Reprendre la musique
    }
    else
    {
        Mix_PauseMusic(); //Mettre en pause la musique
    }
}
