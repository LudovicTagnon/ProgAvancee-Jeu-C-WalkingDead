
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


    //init_menu(&fenetre, &renderer, &textures, &world);
    init_game(&fenetre, &renderer, &textures, &world);

    refresh_menu(renderer, &world, &textures);

    SDL_Delay(10000);

    /*printf("2\n");
    afficherListe(world.Zombie);
    printf("3\n");
    afficherListe(world.vies);
    printf("4\n");
    afficherListe(world.Gun);
    printf("5\n");
    afficherListe(world.Road);
    printf("CST TERRAIN: %i\n", TERRAIN_SIZE);*/

    musique = init_music(musique);
    launch_music(musique);
    prepare_audio(_sample);


    // Boucle principale
    while (!is_game_over(&world)) {

        update_data(&world, &textures, renderer);
        handle_events(&event, renderer, &world, &textures, _sample);
        refresh_graphics(renderer, &world, &textures);
        SDL_Delay(5);
    }

    clean(fenetre, renderer, &textures, &world, _sample);

    SDL_Quit();
    return 0;
}
