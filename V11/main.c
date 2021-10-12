
#include "constants.h"
#include "data.h"
#include "graphics.h"
#include "events.h"
#include "liste.h"

int main()
{

    SDL_Event event;
    world_t world;
    resources_t textures;
    SDL_Renderer *renderer;
    SDL_Window *fenetre;

    time_t t;
    srand((unsigned) time(&t));

    //printf("1\n");
    init(&fenetre, &renderer, &textures, &world);
    printf("2\n");
    //afficherListe(world.Zombie);
    printf("3\n");
    //afficherListe(world.vies);
    printf("4\n");
    //afficherListe(world.Gun);
    printf("5\n");
    //afficherListe(world.Road);
    //printf("CST TERRAIN: %i\n", TERRAIN_SIZE);

	// Boucle principale
	while(!is_game_over(&world)){

        printf("6\n");
        update_data(&world, &textures, renderer);
        printf("7\n");
        handle_events(&event, renderer, &world, &textures);
        printf("8\n");
        refresh_graphics(renderer,&world,&textures);
        //printf("8\n");
        SDL_Delay(5);
    }

    clean(fenetre,renderer,&textures, &world);



    return 0;
}
