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
	int incrementA = points.taille() > 200 ? 1 : ((points.taille() / 100));

	int incrementB = poly2.points.taille() > 200 ? 1 : ((poly2.points.taille() / 100));
	for (int i = 0; i < points.taille(); i += incrementA) // pour tout les points de A
	{
		Segment segmentDeA(points[i], points[((i + incrementA)<points.taille()?(i+incrementA):0)]); // creer tout les segments De A ( 1 a chaque iteration)
		//cout << segmentDeA << endl;
		for (int j = 0; j < poly2.points.taille(); j += incrementB) // pour tout les points de B
		{
			Segment segmentDeB(poly2.points[j], poly2.points[((j + incrementB)<poly2.points.taille() ? (j + incrementB) : 0)]); // creer tout les segments De B
			//	cout << segmentDeB << endl;
			distance = min(distance, segmentDeA.distance(segmentDeB));
		}
	}
	std::cout << "distance entre" << nom << " et " << poly2.nom << " = " << distance << std::endl;
	return distance;
}

double Polygone::aire() const{
    return aire_;
}

inline void Polygone::calculeAire() {
  //  std::cout << "calcule de l'aire de " << nom;
	double  aire = 0;
	int j = points.taille() - 1;
	for (int i = 0; i< points.taille(); ++i)
	{
		aire = aire + points[i].aire(points[j]);
		j = i;
	}
	aire_ =  fabs(aire/2);
	//std::cout << " = " << round(aire_) << std::endl;

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

