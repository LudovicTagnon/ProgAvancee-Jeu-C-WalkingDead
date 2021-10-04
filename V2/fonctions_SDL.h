
int init_sdl(SDL_Window **window, SDL_Renderer **renderer, int width, int height);

SDL_Texture* charger_image(const char* nomfichier, SDL_Renderer* renderer);

SDL_Texture* charger_image_transparente(const char path[], SDL_Renderer *renderer);

void clear_renderer(SDL_Renderer *renderer);

void apply_texture(SDL_Texture *texture,SDL_Renderer *renderer,int x, int y);

void update_screen(SDL_Renderer *renderer);

void clean_texture(SDL_Texture *texture);

void clean_sdl(SDL_Renderer *renderer,SDL_Window *window);
