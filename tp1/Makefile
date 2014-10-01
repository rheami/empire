# Makefile pour TP1.
# Adaptez ce fichier au besoin (si vous ajouter des fichiers).
#
# Choisir l'une des deux configurations (-g: Debug | -O2: Release)
#OPTIONS = -g -O0 -Wall
OPTIONS = -O2 -Wall

all : tp1

tp1 : tp1.cpp point.o segment.o polygone.o tableau.h
	g++ ${OPTIONS} -o tp1 tp1.cpp point.o segment.o polygone.o

point.o : point.cpp point.h
	g++ ${OPTIONS} -c point.cpp

segment.o : segment.cpp segment.h point.h
	g++ ${OPTIONS} -c segment.cpp

polygone.o : polygone.cpp polygone.h point.h segment.h
	g++ ${OPTIONS} -c polygone.cpp

clean:
	rm -rf tp1 *~ *.o

