
#include <SDL2/SDL_mixer.h>
#include "constants.h"
#include "data.h"
#include "graphics.h"
#include "events.h"
#include "audio.h"

int main() {

    SDL_Event event;
    world_t world;
    resources_t textures;
    SDL_Renderer *renderer;
    SDL_Window *fenetre;
    Mix_Chunk *_sample[2];
    Mix_Music *musique;
    time_t t;




    srand((unsigned) time(&t));


    init(&fenetre, &renderer, &textures, &world);
    /*printf("2\n");
    afficherListe(world.Zombie);
    printf("3\n");
    afficherListe(world.vies);
    printf("4\n");
    afficherListe(world.Gun);
    printf("5\n");
    afficherListe(world.Road);
    printf("CST TERRAIN: %i\n", TERRAIN_SIZE);*/

    //Mix_PlayChannel(-1, _sample[1], 99);
    musique = init_music(musique);
    launch_music(musique);
    prepare_audio(_sample);


    // Boucle principale
    while (!is_game_over(&world)) {

        //printf("6\n");
        update_data(&world, &textures, renderer);
        //printf("7\n");
        handle_events(&event, renderer, &world, &textures, _sample);
        //printf("8\n");
        refresh_graphics(renderer, &world, &textures);
        //printf("8\n");
        SDL_Delay(5);
    }

    clean(fenetre, renderer, &textures, &world, _sample);

    SDL_Quit();
    return 0;
}
