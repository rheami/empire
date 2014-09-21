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
	Point(double _x, double _y);
	Point(const Point& point);

	double distance(const Point& point) const;
	const double X() { return x; };
	const double Y() { return y; };
  private:
    double x;
    double y;


  friend std::ostream& operator << (std::ostream&, const Point&);
  friend std::istream& operator >> (std::istream&, Point&);
};

#endif

