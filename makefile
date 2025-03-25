CC = gcc
CPPFLAGS = `sdl2-config --cflags`
CFLAGS = -Wall -Wextra -g -Og
LDFLAGS =
LDLIBS = `sdl2-config --libs`

main: test_graphique.c objets_graphique.c fen.c affichage.c objets_maths.c
	$(CC) $(INC) -o $@ $^ $(CFLAGS)
