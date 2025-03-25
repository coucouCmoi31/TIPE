CC=gcc
CFLAGS=-Wall -Wextra -lm `sdl2-config --cflags`

main: 
	$(CC) test_graph.c objets_graphique.c fen.c affichage.c objets_maths.c -o test_graphique.out $(CFLAGS)


