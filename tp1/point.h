/*
  INF3105 -- Structures de données et algorithmes
  UQAM | Département d'informatique
  Automne 2014 | TP1 | point.h
*/

#if !defined(__POINT_H__)
#define __POINT_H__

#include <iostream>

class Point {
  public:
    Point(){}
	Point(const double _x,const double _y);
	Point(const Point& point);

	double distance(const Point& point) const;
	double X() const { return x; };
	double Y() const { return y; };

	inline Point operator -(const Point& _b) const ;

    // produit scalaire
    inline double operator *(const Point& _b) const;
    // produit d'un nombre avec un vecteur
    Point operator *(const double _b) const;

  private:
    double x;
    double y;


  friend std::ostream& operator << (std::ostream&, const Point&);
  friend std::istream& operator >> (std::istream&, Point&);
};

#endif

