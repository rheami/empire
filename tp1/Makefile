# Makefile pour TP1.
# Adaptez ce fichier au besoin (si vous ajouter des fichiers).
#
CC = g++
# Choisir l'une des deux configurations (-g: Debug | -O2: Release)
OPTIONS = -g -O0 -Wall
#OPTIONS = -O2 -Wall

all: tp1

tp1: tp1.o polygone.o tableau.h
	g++ ${OPTIONS} -o tp1 tp1.o polygone.o point.o segment.o

tp1.o: tp1.cpp
	$(CC) $(OPTION) tp1.cpp

point.o: point.cpp point.h
	$(CC) $(OPTION) -c point.cpp

polygone.o: polygone.cpp polygone.h point.h tableau.h segment.h
	$(CC) $(OPTION) -c polygone.cpp

segment.o: segment.cpp segment.h point.h
	$(CC) $(OPTION) -c segment.cpp

clean:
	rm -rf tp1 *~ *.o

