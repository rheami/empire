/*
  INF3105 -- Structures de données et algorithmes
  UQAM | Département d'informatique
  Automne 2014 | TP1 | polygone.cpp
*/

#include <cmath>
#include <limits>
#include "polygone.h"

// constructeur
Polygone::Polygone(const Point* _points[])
{
}
Polygone::Polygone()
{
}


// destructeur
Polygone::~Polygone() {
	
}


double Polygone::distance(const Polygone& poly2) const
{
    return 0;
}

double Polygone::aire() const{
    return aire_;
}

std::ostream& operator << (std::ostream& os, const Polygone& polygone){
    // À compléter.
	char deuxpoints = ':';
	os << polygone.nom << deuxpoints;


	for (int i = 0; i < polygone.points.taille(); ++i)
	{
		os << polygone.points[i];
	}

	

    return os;
}

std::istream& operator >> (std::istream& in, Polygone& polygone){
    // À compléter­.
    char c;
    do{
		polygone.points.ajouter(Point()); // preparer l<espace pour le point dans le tableau
		in >> polygone.points[polygone.points.taille()-1] >> c >> std::ws;
    }while(c==',');
    assert(c==';');
    return in;
}

