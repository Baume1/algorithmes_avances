opt = -c -Wall -Wextra -std=c11

main.exe : p_texte_enrichi.o main.o p_nanodom.o
	gcc -o main.exe main.o p_texte_enrichi.o p_nanodom.o


p_texte_enrichi.o : p_texte_enrichi.c p_texte_enrichi.h
	gcc ${opt} p_texte_enrichi.c

p_nanodom.o : p_nanodom.c p_nanodom.h
	gcc ${opt} p_nanodom.c

main.o: main.c
	gcc ${opt} main.c

clean :
	rm *.o
	rm *.exe