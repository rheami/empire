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
	Polygone* Plusgrand = NULL;

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

void MethodeDeuxPolygone(Tableau<Polygone*> &Carte, double DM)
{
	Polygone* PolyA = NULL;
	Polygone* PolyB = NULL;
	double aire = 0;


	//calcule l'aire des poligones individuels ce qui nous permet d'eviter d'evaluer la distance pour tout groupe de polygones de aillant une aire inferieur a celle du polygone le plus grand
	for (int i = 0; i < Carte.taille(); ++i)
	{
		if (aire < Carte[i]->aire())
		{
			aire = Carte[i]->aire();
			PolyA = Carte[i];
			PolyB = NULL;
		}
	}




	for (int i = 0; i < Carte.taille(); ++i)
	{
		for (int j = i+1; j < Carte.taille(); ++j)
		{
			if ( ((Carte[i]->aire()+Carte[j]->aire())>aire)
                && (DM>=Carte[i]->distance(*Carte[j])) )
			{
				PolyA = Carte[i];
				PolyB = Carte[j];
				aire = Carte[i]->aire() + Carte[j]->aire();
			}
			//std::cout << "distance " << Carte[i]->getNom() << " " << Carte[j]->getNom() << " : " << Carte[i]->distance(*Carte[j]) << std::endl;
		}
	}



	if (PolyB)
	{
		
		std::cout << round(aire) << std::endl << PolyA->getNom() << std::endl << PolyB->getNom() << std::endl;
	}
	else
	{
		std::cout << round(aire) << std::endl << PolyA->getNom() << std::endl;
	}

}


inline bool Connect(const Tableau<Tableau<bool>>& matriceConnectivite, const int a , const int b)
{
	return (matriceConnectivite[a][b] || matriceConnectivite[b][a]);
}

void MethodeTroisPolygone(Tableau<Polygone*> &Carte, double DM,int nb)
{


	int PolyA = 0;
	int PolyB = -1;
	double aire = 0;


	//calcule l'aire des poligones individuels ce qui nous permet d'eviter d'evaluer la distance pour tout groupe de polygones de aillant une aire inferieur a celle du polygone le plus grand
	for (int i = 0; i < Carte.taille(); ++i)
	{
		if (aire < Carte[i]->aire())
		{
			aire = Carte[i]->aire();
			PolyA = i;
		}
	}


	Tableau<Tableau<bool>> matriceConnectivite;



	for (int i = 0; i < Carte.taille(); ++i)
	{
		for (int j = i + 1; j < Carte.taille(); ++j)
		{
			if ((DM >= Carte[i]->distance(*Carte[j])))
			{
				while (matriceConnectivite.taille() <= i)
				{
					matriceConnectivite.ajouter(Tableau<bool>());
				}
				while (matriceConnectivite[i].taille() < j)
				{
					matriceConnectivite[i].ajouter(false);
				}
				matriceConnectivite[i].ajouter(true);
			}
			//std::cout << "distance " << Carte[i]->getNom() << " " << Carte[j]->getNom() << " : " << Carte[i]->distance(*Carte[j]) << std::endl;
		}
	}




	for (int i = 0; i < Carte.taille(); ++i)
	{
		for (int j = i + 1; j < Carte.taille(); ++j)
		{
			if (((Carte[i]->aire() + Carte[j]->aire())>aire)
				&& (Connect(matriceConnectivite, i, j)))
			{
				PolyA = i;
				PolyB = j;
				aire = Carte[i]->aire() + Carte[j]->aire();
			}
			//std::cout << "distance " << Carte[i]->getNom() << " " << Carte[j]->getNom() << " : " << Carte[i]->distance(*Carte[j]) << std::endl;
		}
	}
	Tableau<int> Poly;

	Poly.ajouter(PolyA);
	if (PolyB !=-1)
	Poly.ajouter(PolyB);

	for (int p = Poly.taille()-1; p < nb; ++p)
	{
		PolyA = -1;
		aire = 0;
		for (int i = 0; i < Poly.taille(); ++i)
		{
			for (int j = i + 1; j < Carte.taille(); ++j)
			{
				if ((aire < Carte[j]->aire()) && (!Poly.contient(j)) && (Connect(matriceConnectivite, Poly[i], j)))
				{
					aire = Carte[j]->aire();
					PolyA = j;
				}
			}
		}
		if (PolyA != -1)
		Poly.ajouter(PolyA);
	}
	aire = 0;

	for (int i = 0; i < Poly.taille(); ++i)
	{
		aire += Carte[i]->aire();
	}


	std::cout << round(aire) << std::endl;
	for (int i = 0; i < Poly.taille(); ++i)
	{
		std::cout << Carte[Poly[i]]->getNom() << std::endl;
	}


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
    }


    switch(nbRegions){
        case 1:
        {
			MethodeUnPolygone(Carte);
            break;
        }
        case 2:
        {

			MethodeDeuxPolygone(Carte,DM);
            break;
        }
        default:
			MethodeTroisPolygone(Carte, DM, nbRegions);
            break;
    }

	// Netoyage de la memoire
	for (int i = 0; i < Carte.taille(); ++i)
	{
		delete Carte[i];
	}
    return 0;
}
