
#if !defined(__VECTEUR_H__)
#define __VECTEUR_H__


class Vecteur{
  public:
	  Vecteur(double vx_ = 0, double vy_  = 0): vx(vx_), vy(vy_){};
	Vecteur& operator +=(const Vecteur& v);
	Vecteur operator + (const Vecteur&) const;
  private:
 double vx, vy;
};

#endif