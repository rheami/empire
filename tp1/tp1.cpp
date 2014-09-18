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
        string nom;
        Polygone *polygone = new Polygone;
        char deuxpoints;
        in >> nom >> deuxpoints >> *polygone >> std::ws;
        assert(deuxpoints==':');
		Carte.ajouter(polygone);
    }

    switch(nbRegions){
        case 1:
        {
            cout << round(Carte[0]->aire()) << endl;
			cout << Carte[0]->getNom() << endl;
            break;
        }
        case 2:
        {
            cout << round(0) << endl;
            cout << "A" << endl;
            cout << "B" << endl;
            break;
        }
        default:
            cout << "Ce programme ne supporte pas 3 régions ou plus!" << endl;
            break;
    }

    return 0;
}
