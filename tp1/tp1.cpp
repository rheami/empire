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


void MethodeUnPolygone(const Tableau<Polygone*> &Carte)
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

void MethodeDeuxPolygone(const Tableau<Polygone*> &Carte,const double DM)
{
	Polygone* PolyA = NULL;
	Polygone* PolyB = NULL;
	double aire = 0;


	//cherche l'aire du polygone le plus grand
	for (int i = 0; i < Carte.taille(); ++i)
	{
		if (aire < Carte[i]->aire())
		{
			aire = Carte[i]->aire();
			PolyA = Carte[i];
		}
	}



	//calcul de l'aire des couples de polygones si leur aire combine est superieur a celle du polygone ou couple de polygones actuel on verifie la distance
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


inline bool isConnected(const Tableau<Tableau<bool> > & matriceConnectivite, const int a , const int b)
{
	return (matriceConnectivite[a][b] || matriceConnectivite[b][a]);
}

/*
inline bool isConnected(const Tableau<Tableau<bool> > & matriceConnectivite, const int a, const int b)
{
	const Tableau<bool> * tableauA = &(matriceConnectivite[a]);
	const Tableau<bool> * tableauB = &(matriceConnectivite[b]);
	if (tableauA->operator[](b))
		return true;
	if (tableauB->operator[](a))
		return true;
	return (matriceConnectivite[a][b] || matriceConnectivite[b][a]);
}*/
void MethodeTroisPolygone(const Tableau<Polygone*> &Carte,const double DM,const int nb)
{


	int PolyA = 0;
	int PolyB = -1;
	double aire = 0;


	//calcule l'aire des polygones individuels ce qui nous permet d'eviter d'evaluer la distance pour tout groupe de polygones de aillant une aire inferieur a celle du polygone le plus grand
	for (int i = 0; i < Carte.taille(); ++i)
	{
		if (aire < Carte[i]->aire())
		{
			aire = Carte[i]->aire();
			PolyA = i;
		}
	}


	//On battit une matrices de boolean representant les couples de polygones dont la distance est inferieur a DM 

	Tableau<Tableau<bool> > matriceConnectivite;


	//Remplir la dite matrice avec les couples valides on rempli uniquement la moitie car (DM(A,B)) = (DM(B,A))
	for (int i = 0; i < Carte.taille(); ++i)
	{
		matriceConnectivite.ajouter(Tableau<bool>());
		for (int j = 0; j < Carte.taille(); ++j)
		{
			if ((j>=i+1) && (DM >= Carte[i]->distance(*Carte[j])))
			{
				matriceConnectivite[i].ajouter(true);
			}
			else
			{
				matriceConnectivite[i].ajouter(false);
			}

		}
	}


	//on verifie les paires de taille interessante
	for (int i = 0; i < Carte.taille(); ++i)
	{
		for (int j = i + 1; j < Carte.taille(); ++j)
		{
			if (((Carte[i]->aire() + Carte[j]->aire())>aire)
				&& (isConnected(matriceConnectivite, i, j)))
			{
				PolyA = i;
				PolyB = j;
				aire = Carte[i]->aire() + Carte[j]->aire();
			}
		}
	}

	//tableau des polygones trouve
	Tableau<int> Poly;

	//Ajouter le polygone de la plus grande taille trouve
	Poly.ajouter(PolyA);

	//ajouter le second polygone du couple si un couple as ete trouve
	if (PolyB !=-1)
	Poly.ajouter(PolyB);


	//on parcoure tout les polygones qui peuvent etre ajouter a l'empire 
	for (int p = Poly.taille(); p < nb; ++p)
	{
		PolyA = -1;
		aire = 0;
		for (int i = 0; i < Poly.taille(); ++i)
		{
			for (int j = i + 1; j < Carte.taille(); ++j)
			{
				if ((aire < Carte[j]->aire()) && (!Poly.contient(j)) && (isConnected(matriceConnectivite, Poly[i], j)))
				{
					aire = Carte[j]->aire();
					PolyA = j;
				}
			}
		}
		if (PolyA != -1)
		Poly.ajouter(PolyA);
	}

	//on remet l'aire a 0 et on s'en resert pour calculer l'aire totale de l'assemblage trouve
	aire = 0;

	for (int i = 0; i < Poly.taille(); ++i)
	{
		aire += Carte[i]->aire();
	}

	//affichage de l'aire arondi
	std::cout << round(aire) << std::endl;
	//afichage de tout les polygones trouve
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
