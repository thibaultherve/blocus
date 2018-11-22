blocus: menu.o jeu.o main.o gagnant.o
	gcc -o blocus menu.o jeu.o main.o gagnant.o -lgraph -std=c89

menu.o: menu.c
	gcc -o menu.o -c menu.c -lgraph -std=c89

jeu.o: jeu.c
	gcc -o jeu.o -c jeu.c -lgraph -std=c89

gagnant.o: gagnant.c
	gcc -o gagnant.o -c gagnant.c -lgraph -std=c89

main.o: main.c menu.h jeu.h
	gcc -o main.o -c main.c -lgraph -std=c89

clean:
	rm main.o menu.o jeu.o *.*~
