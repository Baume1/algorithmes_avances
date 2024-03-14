opt =
all: main clean

main: main.o terminaux.o non_terminaux.o
	gcc -o ${opt} main main.o terminaux.o non_terminaux.o

main.o: main.c main.h
	gcc -c ${opt} main.c

terminaux.o : terminaux.c terminaux.h main.h
	gcc -c ${opt} terminaux.c

non_terminaux.o : non_terminaux.c non_terminaux.h main.h
	gcc -c ${opt} non_terminaux.c


clean:
	del *.o main.exe
