/*
  INF3105 -- Structures de données et algorithmes
  UQAM | Département d'informatique
  Automne 2014 | TP1 | polygone.cpp
*/

#include <cmath>
#include <limits>
#include "polygone.h"
#include "Segment.h"
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


// distance minimale entre deux polygones
double Polygone::distance(const Polygone& poly2) const
{
    double distance = std::numeric_limits<double>::infinity();

    for (int i = 0; i < points.taille(); ++i) // pour tout les points de A
    {
	Segment segmentDeA(points[i], points[(i + 1)%points.taille()]); // creer tout les segments De A ( 1 a chaque iteration)
	for (int j = 0; j < poly2.points.taille(); ++j) // pour tout les points de B
	{
            Segment segmentDeB(poly2.points[j], poly2.points[(j + 1)%points.taille()]); // creer tout les segments De B
            distance = min(distance, segmentDeA.distance(segmentDeB));
	}
    }
    return distance;
}

double Polygone::aire() const{
    return aire_;
}

inline void Polygone::calculeAire() {

	double  aire = 0;
	int j = points.taille() - 1;
	for (int i = 0; i< points.taille(); ++i)
	{
		aire = aire + points[i].aire(points[j]);
		j = i;
	}
	aire_ =  fabs(aire/2);

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

	string nom;

	char deuxpoints;
	in >> nom >> deuxpoints;

    char c;
    do{
		polygone.points.ajouter(Point()); // preparer l<espace pour le point dans le tableau
		in >> polygone.points[polygone.points.taille()-1] >> c >> std::ws;
    }while(c==',');
    assert(c==';');

    polygone.calculeAire();
	polygone.nom = nom;

    return in;
}

