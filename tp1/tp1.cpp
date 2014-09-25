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

	// Netoyage de la memoire
	for (int i = 0; i < Carte.taille(); ++i)
	{
		delete Carte[i];
	}
    return 0;
}
