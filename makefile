CC=gcc
CFLAGS=-std=c11 -Wpedantic -Wall -Wextra
LDLIBS=-lm
RM=rm -f
OBJ=main.o identite.o genea.o
EXE=main
# Pour produire le fichier exécutable
$(EXE):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE) $(LDLIBS)
# Pour produire les fichiers objets
main.o:main.c identite.h genea.h
	$(CC) $(CFLAGS) -c main.c
identite.o:identite.c identite.h
	$(CC) $(CFLAGS) -c identite.c
genea.o:genea.c genea.h
	$(CC) $(CFLAGS) -c genea.c

# Pour effacer les objets et les exécutables
clean:
	$(RM) $(OBJ) $(EXE) 