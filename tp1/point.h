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

	Point operator-(const Point& autre) const;
    Point operator+(const Point& autre) const;

    // produit scalaire
    double operator*(const Point& autre) const;
    // produit d'un nombre avec un vecteur
    Point operator*(const double autre) const;

  private:
    double x;
    double y;


  friend std::ostream& operator << (std::ostream&, const Point&);
  friend std::istream& operator >> (std::istream&, Point&);
};

inline double min(double a, double b){
	return a < b ? a : b;
}
#endif

