CC = gcc
CFLAGS = -W -Wall -ansi -std=c99 -g
LIBS = -L./SDL2_ttf/.libs -L./SDL2_image/.libs -L./SDL2_mixer/.libs 
LDFLAGS = `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lSDL2_ttf -lSDL2_mixer#-ogg_mp3 
INCLUDES = -I./SDL2_ttf -I./SDL2_image
EXEC = main
SRC = main.c fonctions_SDL.c data.c events.c graphics.c liste.c audio.c
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
