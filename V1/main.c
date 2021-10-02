
#include "constants.h"
#include "data.h"
#include "graphics.h"
#include "events.h"

int main()
{

    SDL_Event event;
    world_t world;
    resources_t textures;
    SDL_Renderer *renderer;
    SDL_Window *fenetre;

    time_t t;
    srand((unsigned) time(&t));

    printf("1\n");

    init(&fenetre, &renderer, &textures, &world);
    printf("2\n");

    printf("CST ZOMBIES: %i\n", NUMBER_ZOMBIES);
    printf("NB ZOMBIES: %i\n", world.nb_zombies);
    printf("CST TERRAIN: %i\n", TERRAIN_SIZE);

	// Boucle principale
	while(!is_game_over(&world)){
        printf("3\n");

        refresh_graphics(renderer,&world,&textures);

        printf("4\n");

        update_data(&world, &textures, renderer);

        //printf("5\n");

        handle_events(&event, renderer, &world, &textures);
        //printf("6\n");

        SDL_Delay(10);
    }
    //printf("7\n");

    clean(fenetre,renderer,&textures, &world);
    printf("8\n");


    return 0;
}
