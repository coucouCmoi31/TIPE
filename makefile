CC=gcc
CFLAGS=-lm -lSDL2_ttf -Ofast -g
CPPFLAGS = `pkg-config --cflags --libs sdl2 SDL2_ttf`

main: 
	$(CC) test_graph.c objets_graphique.c fen.c affichage.c objets_maths.c -o test_graphique.out $(CFLAGS) $(CPPFLAGS)

run:
	./test_graphique.out



