/*
  INF3105 -- Structures de données et algorithmes
  UQAM | Département d'informatique
  Automne 2014 | TP1 | tp1.cpp
*/

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <limits>
#include "polygone.h"
#include "tableau.h"

using namespace std;


void MethodeUnPolygone(Tableau<Polygone*> &Carte)
{


	Polygone* Plusgrand;

	int aire = 0;
	for (int i = 0; i < Carte.taille(); ++i)
	{
		if (aire < Carte[i]->aire())
		{
			aire = Carte[i]->aire();
			Plusgrand = Carte[i];
		}
	}
	cout << round(Plusgrand->aire()) << endl;
	cout << Plusgrand->getNom() << endl;


}

void MethodeDeuxPolygone(Tableau<Polygone*> &Carte)
{
	Polygone* Plusgrand;

	double aire = 0;
	for (int i = 0; i < Carte.taille(); ++i)
	{
		for (int j = 0; j < Carte.taille(); ++j)
		{
			std::cout << "disance " << Carte[i]->getNom() << " " << Carte[j]->getNom() << " : " << Carte[i]->distance(*Carte[j]) << std::endl;
		}
	}


}

double distancePointASegmentCD(Point& pointA , Point& pointC, Point& pointD) {
    Point CA = pointA - pointC;
    Point CD = pointD - pointC;
    double ratio = (CA * CD) / (CD * CD);
    ratio = ratio > 1 ? 1 : ratio;
    Point projectionAsurCD = CD * ratio; // note: ne pas faire ratio * CD
    Point pointE = pointC + projectionAsurCD;
    return pointA.distance(pointE);
}

void testppoints(){
    Point A = Point(3, 3);
    Point C = Point(1, 1);
    Point D = Point(7, 1);
    Point CA = A - C;
    Point CD = D - C;
    double num = CA * CD;
    double denum = CD * CD;
    cout << "CA : " << A << "-" << C << "=" << CA << endl;
    cout << "CD : " << D << "-" << C << "=" << CD << endl;
    cout << "CA * CD : " << num << endl;
    cout << "CD * CD : " << denum << endl;
    double ratio = num/denum;
    ratio = ratio > 1 ? 1 : ratio;
    cout << "ratio : " << ratio << endl;
    Point projection = CD*ratio; // note: ne pas faire ratio * CD
    cout << projection << endl;
    Point E = C + projection;
    cout << "E = " << E << endl;
    cout << "distance AE = " << A.distance(E) << endl;
    A = Point(9, 1);
    CA = A - C;
    num = CA * CD;
    cout << "CA : " << A << "-" << C << "=" << CA << endl;
    cout << "CD : " << D << "-" << C << "=" << CD << endl;
    cout << "CA * CD : " << num << endl;
    cout << "CD * CD : " << denum << endl;
    ratio = num/denum;
    cout << "ratio : " << ratio << endl;
    ratio = ratio > 1 ? 1 : ratio;
    projection = CD*ratio; // note: ne pas faire ratio * CD
    cout << projection << endl;
    E = C + projection;
    cout << "E = " << E << endl;
    cout << "distance AE = " << A.distance(E) << endl;
    cout << distancePointASegmentCD(A, C, D) << endl;
}

int main(int argc, const char** argv){

	if(argc<3){
        cout << "./tp1 carte.txt nbRegions [distMax]" << endl;
        return 1;
    }

    const char* fichiercarte = argv[1];
    int nbRegions = atoi(argv[2]);
    double DM = argc>=4 ? atof(argv[3]) : numeric_limits<double>::infinity();
    assert(DM>=0);

    ifstream in(fichiercarte);
    if(in.fail()){
        cout << "Imposible de lire le fichier " << fichiercarte << endl;
        return 2;
    }
	Tableau<Polygone*> Carte;
    while(!in.eof()){
        Polygone *polygone = new Polygone;
        in >>  *polygone >> std::ws;
		Carte.ajouter(polygone);
		cout << polygone->getNom() << polygone->aire() << endl;
    }


    switch(nbRegions){
        case 1:
        {
			MethodeUnPolygone(Carte);
            break;
        }
        case 2:
        {

			MethodeDeuxPolygone(Carte);
            break;
        }
        default:
            cout << "Ce programme ne supporte pas 3 régions ou plus!" << endl;
            break;
    }

    testppoints();
	// Netoyage de la memoire
	for (int i = 0; i < Carte.taille(); ++i)
	{
		delete Carte[i];
	}
    return 0;
}
