#include "Vecteur.h"


Vecteur& Vecteur::operator += (const Vecteur& autre) {
	vx += autre.vx; vy += autre.vy;
	return *this;
}

Vecteur Vecteur::operator + (const Vecteur& autre) const{
	return Vecteur(vx + autre.vx, vy + autre.vy);
}

