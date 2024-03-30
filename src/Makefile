opt = 
all: main clean

main: main.o terminaux.o non_terminaux.o arbre.o affichage.o
	gcc -o main main.o terminaux.o non_terminaux.o arbre.o affichage.o

main.o: main.c main.h
	gcc -c ${opt} main.c

terminaux.o : terminaux.c terminaux.h main.h
	gcc -c ${opt} terminaux.c

non_terminaux.o : non_terminaux.c non_terminaux.h main.h
	gcc -c ${opt} non_terminaux.c

arbre.o : arbre.c arbre.h
	gcc -c ${opt} arbre.c

affichage.o : affichage.c affichage.h
	gcc -c ${opt} affichage.c

clean:
	del *.o 
