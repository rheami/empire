/*
  INF3105 -- Structures de données et algorithmes
  UQAM | Département d'informatique
  Automne 2014 | TP1 | polygone.h
*/

#if !defined(__POLYGONE_H__)
#define __POLYGONE_H__
#include <iostream>
#include "point.h"
#include "tableau.h"
#include "vecteur.h"
#include <string>

using namespace std;


class Polygone {
  public:
    double distance(const Polygone& poly2) const;
    double aire() const; // getter sur la propriete aire_

  // constructeur
	Polygone(const Point* points[]) :points(0)
	{
	// ajoute les points



	}
	Polygone() :points(0), aire_(0),sommets(0) {}

	// destructeur
	~Polygone(){
		delete[] points;
	}
    
	const inline std::string getNom()const { return nom; };
    // calcule  l<aire a la creation



  private:
    // Représentation : à compléter.
    int sommets; // nombre de sommets (ou de cotes)
    Point* points;
    double aire_;

    std::string nom;

  friend std::ostream& operator << (std::ostream&, const Polygone&);
  friend std::istream& operator >> (std::istream&, Polygone&);
};

#endif

