/*
  INF3105 -- Structures de données et algorithmes
  UQAM | Département d'informatique
  Automne 2014 | TP1 | polygone.cpp
*/

#include <cmath>
#include <limits>
#include "polygone.h"
#include "segment.h"
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
	// si le polygone a moins de 10 points : évaluer touts les segments
	// le polygone a plus de 10 points : évaluer sur 10 points (aproximation de la distance sur l'enveloppe)
	// et recalculer sur les points de la section (on divise par 10)

	int departA = 0;
	int departB = 0;
	int finA = points.taille();
	int finB = poly2.points.taille();
	int incrementA;
	int incrementB;
	int nbdiv =10;
	do
	{
		incrementA = max(( abs(finA - departA) / nbdiv), 1); 
		incrementB = max(( abs(finB - departB) / nbdiv), 1);
		
		// pour les 100 points de A
		for (int i = departA; i < finA; i += incrementA) 
		{
			// creer les segments de l'enveloppe De A
			departA = i;
			finA = (i + incrementA) < points.taille() ? (i + incrementA) : 0;
			Segment segmentDeA(points[departA], points[finA]);
			//cout << "A " << departA << " -> " << finA << endl;
			// pour tout les 100 points de B
			for (int j = departB; j < finB; j += incrementB)
			{
				// creer les segments de l'enveloppe De B
				departB = j;
				finB = (j + incrementB) < poly2.points.taille() ? (j + incrementB) : 0;
				Segment segmentDeB(poly2.points[departB], poly2.points[finB]);
				//cout << "B " << departB << " -> " << finB << endl;
				distance = min(distance, segmentDeA.distance(segmentDeB));
			}
		}

	} while (incrementA != 1 || incrementB != 1);
	
	//std::cout << "distance entre" << nom << " et " << poly2.nom << " = " << distance << std::endl;
	//std::cout << "distance entre" << nom << " et " << poly2.nom << " = " << distance << std::endl;
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

