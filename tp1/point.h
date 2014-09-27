/*
  INF3105 -- Structures de données et algorithmes
  UQAM | Département d'informatique
  Automne 2014 | TP1 | point.h
*/

#if !defined(__POINT_H__)
#define __POINT_H__
#include <math.h>
#include <iostream>

class Point {
  public:
    Point(){}
	Point(const double _x,const double _y);
	Point(const Point& point);

    Point operator-(const Point& autre) const{
		return Point(x - autre.x, y - autre.y);
	}

    Point operator+(const Point& autre) const{
		return Point(x + autre.x, y + autre.y);
	}

	// produit scalaire
	double operator*(const Point& autre) const{
		return x*autre.x + y*autre.y;
	}
	// produit d'un nombre avec un vecteur
	Point operator*(const double autre) const{
		return Point(x*autre, y*autre);
	}

	double area(const Point& point) const {
		return (point.x + x) * (point.y - y);
	}

	double distance(const Point& point) const {
		double dx = x - point.x,
			dy = y - point.y;
		return sqrt(dx*dx + dy*dy);
	}


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

