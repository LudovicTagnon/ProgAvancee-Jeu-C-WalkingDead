
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

    FILE *file_r;
    file_r = fopen("Save.txt","r");
    if(file_r == NULL)
    {
        printf("Error!");
        exit(1);
    }

    //init_menu(&fenetre, &renderer, &textures, &world);
    init_game(&fenetre, &renderer, &textures, &world);

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
        if(world.quit_menu==0){
            handle_events(&event, renderer, &world, &textures, _sample, file_r);
            update_menu(&world, &textures, renderer);
            refresh_menu(renderer, &world, &textures);
        }else{
            refresh_graphics(renderer, &world, &textures);
            update_data(&world, &textures, renderer);
            handle_events(&event, renderer, &world, &textures, _sample, file_r);
        }
        SDL_Delay(5);
    }



    FILE *file_w;
    file_w = fopen("Save.txt","w");
    if(file_w == NULL)
    {
        printf("Error!");
        exit(1);
    }
    writedata(file_w, &world);


    clean(fenetre, renderer, &textures, &world, _sample);

    SDL_Quit();
    return 0;
}
