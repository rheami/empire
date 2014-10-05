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

	int depart_A = 0;
	int depart_B = 0;
	int fin_A = points.taille();
	int fin_B = poly2.points.taille();
	int incrementA;
	int incrementB;
	int nbdiv = 10;
	do
	{
		int departA = depart_A;
		int finA = fin_A;
		int departB = depart_B;
		int finB = fin_B;

		incrementA = max(( abs(finA - departA) / nbdiv), 1); 
		incrementB = max(( abs(finB - departB) / nbdiv), 1);

		// pour les nbdiv points de A
		//cout << "A " << departA << " -> " << finA << endl;
		for (int i = departA; i < finA; i += incrementA) 
		{
			// creer les segments de l'enveloppe De A
			int nextA = (i + incrementA) < points.taille() ? (i + incrementA) : 0;
			Segment segmentDeA(points[i], points[nextA]);
			//cout << i << " -> " << nextA << endl;
			// pour tout les nbdiv points de B
			//cout << "B " << departB << " -> " << finB << endl;
			for (int j = departB; j < finB; j += incrementB)
			{
				// creer les segments de l'enveloppe De B
				int nextB = (j + incrementB) < poly2.points.taille() ? (j + incrementB) : 0;
				Segment segmentDeB(poly2.points[j], poly2.points[nextB]);
				//cout << j << " -> " << nextB << endl;
				//cout << "B " << departB << " -> " << finB << endl;
				double distanceTmp = segmentDeA.distance(segmentDeB);
				//cout << "distance = " << distanceTmp << endl;
				if (distanceTmp < distance) {
					distance = distanceTmp;
					depart_A = i;
					fin_A = nextA;
					depart_B = j;
					fin_B = nextB;
				}
			}
		}

	} while (incrementA != 1 || incrementB != 1);
	
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

