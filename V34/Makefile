CC = gcc
CFLAGS = -W -Wall -ansi -std=c99 -g
LIBS = -L./SDL2_ttf/.libs -L./SDL2_image/.libs -L./SDL2_mixer/.libs  -L./SDL2_gfx/.libs
LDFLAGS = `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx
INCLUDES = -I./SDL2_ttf -I./SDL2_image -I./SDL2_gfx
EXEC = main
SRC = main.c fonctions_SDL.c data.c logic.c colision.c events.c graphics.c liste.c audio.c saving.c
OBJ = $(SRC:.c=.o) -lm

all: $(EXEC)
main: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
clean:
	rm -rf *.o *~
mrproper: clean
	rm -rf $(EXEC)
