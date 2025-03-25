CC=gcc
CFLAGS=-lm
CPPFLAGS = `sdl2-config --libs`

main: 
	$(CC) test_graph.c objets_graphique.c fen.c affichage.c objets_maths.c -o test_graphique.out $(CFLAGS) $(CPPFLAGS)




