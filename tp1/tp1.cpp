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



	//cherche le couples de polygones ayant la plus grande aire et qui respecte la distance
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

// verifie si deux polygones sont relies (selon la matrice)
void IncrementerTableau(Tableau<int>& GroupeNPoly,int pos, int taille)
{
	if (pos == 0 && GroupeNPoly[pos] == taille - (GroupeNPoly.taille() - pos))
		++GroupeNPoly[pos];
	else if (GroupeNPoly[pos] == taille-(GroupeNPoly.taille()-pos))
	{
		IncrementerTableau(GroupeNPoly, pos - 1, taille);
			GroupeNPoly[pos] = min(GroupeNPoly[pos - 1]+1,taille);

		
	}
	else
		++GroupeNPoly[pos];
}

void TesterGroupeSuivant(Tableau<int>& GroupeNPoly, int taille)
{
	IncrementerTableau(GroupeNPoly, GroupeNPoly.taille() - 1, taille);
	//std::cout << "taille" << taille<<std::endl;

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
void MethodeTroisPlusPolygone(const Tableau<Polygone*> &Carte, const double DM, const int nb)
{


	int PolyA = 0;
	int PolyB = -1;
	double aire = 0;


	//cherche l'aire du polygone le plus grand
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

	for (int i = 0; i < Carte.taille(); ++i)
	{
		matriceConnectivite.ajouter(Tableau<bool>());
		for (int j = 0; j < Carte.taille(); ++j)
		{
			if ((j >= i + 1) && (DM >= Carte[i]->distance(*Carte[j])))
			{
				matriceConnectivite[i].ajouter(true);
			}
			else
			{
				matriceConnectivite[i].ajouter(false);
			}

		}
	}


	//cherche le couples de polygones ayant la plus grande aire et qui respecte la distance
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
	if (PolyB != -1)
		Poly.ajouter(PolyB);




	//Ce tableau peut etre interprete a la fois comme la liste des polygones du groupe et comme la liste des indices de plusieurs boucles encastre et en les logeant dans un tableau le nombre de boucles encastre peut varrier a volonte 
	Tableau<int> GroupeNPoly;

	//Limiter le nombre de polygone au nombre maximal dans la carte
	int QuantitePolygoneCible = min(nb, (Carte.taille()));
	
	// on initialise les polygones a 0,1,2....n de cette facon on saute la moitie des test redondants
	for (int i = 0; i <QuantitePolygoneCible; i++)
	{

		GroupeNPoly.ajouter(i);
	}


	do
	{
		// la methode TesterGroupeSuivant incremente les indices des boucles encastre tour a tours de facon recurcive
		for (; (GroupeNPoly[GroupeNPoly.taille() - 1]) < Carte.taille(); TesterGroupeSuivant(GroupeNPoly, Carte.taille() - 1))
		{

			//aire locale les groupes plus complex ont besoin d'une variable locale pour accumuler la somme de leur aire
			int laire = 0;
			for (int i = 0; i < GroupeNPoly.taille(); ++i)
			{
				//	std::cout << i; 
				//std::cout << " ";
				//	std::cout << GroupeNPoly[i];
				//std::cout << " ";
				//	std::cout << Carte[GroupeNPoly[i]]->aire();
				//std::cout << std::endl;
				laire += Carte[GroupeNPoly[i]]->aire();
			}

			//si l'aire du polygone local est inferieur a la meuilleur a ce jours on n'effectu pas les tests suivants
			if (laire > aire)
			{
				//on veifie que tout les polygones peuvent etre relier a au moins un des polygones precedents 
				bool Connected = true;
				for (int i = 1; i < GroupeNPoly.taille() && Connected == true; ++i)
				{
					Connected = false;
					//si un des polygones echoue le test de connectivite on saute au groupe suivant
					for (int j = 0; j < i; ++j)
					{
						if (isConnected(matriceConnectivite, i, GroupeNPoly[j]))
						{
							Connected = true;
							break;
						}
					}
				}
				// si le polygone succede au tete de connectivite le meuilleur resultat est remplace par le resultat actuel
				if (Connected == true)
				{
					Poly = GroupeNPoly;
					aire = laire;
				}
			}
		}
		//si aucun groupe de QuantitePolygoneCible de polygone n'as ete trouve on diminue de 1 et on recommence
		if (GroupeNPoly.taille() != Poly.taille())
		{
			--QuantitePolygoneCible;
			for (int i = 0; i < QuantitePolygoneCible; i++)
			{

				GroupeNPoly[i] = i;

			}
			GroupeNPoly.enlever_dernier();
		}
	} while (GroupeNPoly.taille() != Poly.taille() && QuantitePolygoneCible>2);
	
	//on remet l'aire a 0 et on s'en resert pour calculer l'aire totale de l'assemblage trouve
	aire = 0;

	for (int i = 0; i < Poly.taille(); ++i)
	{
		aire += Carte[Poly[i]]->aire();
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
			MethodeTroisPlusPolygone(Carte, DM, nbRegions);
            break;
    }

	// Netoyage de la memoire
	for (int i = 0; i < Carte.taille(); ++i)
	{
		delete Carte[i];
	}
	
    return 0;
}
