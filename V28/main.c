
#include <SDL2/SDL_mixer.h>
#include "constants.h"
#include "data.h"
#include "graphics.h"
#include "events.h"
#include "audio.h"
#include "liste.h"

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


    init_game(&fenetre, &renderer, &textures, &world);

    musique = init_music(musique);
    launch_music(musique);
    prepare_audio(_sample);

    FILE *file_r;

    //afficherListe(world.tree);

    // Boucle principale
    while (!is_game_over(&world)) {
        if(world.quit_menu==0){
            handle_events(&event, renderer, &world, &textures, _sample, file_r);
            update_menu(&world, &textures, renderer);
            refresh_menu(renderer, &world, &textures);
        }else{
            refresh_graphics(renderer, &world, &textures);
            update_data(&world, &textures, renderer);
            handle_events(&event, renderer, &world, &textures, _sample, file_r);
        }
        SDL_Delay(3);
    }



    FILE *file_w;
    writedata(file_w, &world);


    clean(fenetre, renderer, &textures, &world, _sample);

    SDL_Quit();
    return 0;
}
