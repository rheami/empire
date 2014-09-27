/*
  INF3105 -- Structures de données et algorithmes
  UQAM | Département d'informatique
  Automne 2014 | TP1 | point.cpp
*/

#include <assert.h>
#include <math.h>
#include "point.h"

Point::Point(const Point& point)
  : x(point.x), y(point.y)
{
}

Point::Point(const double _x, const double _y)
  : x(_x), y(_y)
{}

Point Point::operator-(const Point& autre) const{
    return Point(x-autre.x, y-autre.y);
}
Point Point::operator+(const Point& autre) const{
    return Point(x+autre.x, y+autre.y);
}

// produit scalaire
double Point::operator*(const Point& autre) const{
    return x*autre.x + y*autre.y;
}
// produit d'un nombre avec un vecteur
Point Point::operator*(const double autre) const{
    return Point(x*autre, y*autre);
}

double Point::distance(const Point& point) const {
    double dx=x-point.x,
           dy=y-point.y;
    return sqrt(dx*dx + dy*dy);
}

double Point::aire(const Point& point) const {
    return (point.x + x) * (point.y - y);
}



std::ostream& operator << (std::ostream& os, const Point& point) {
  os << "(" << point.x << "," << point.y << ")";
  return os;
}

std::istream& operator >> (std::istream& is, Point& point) {
  char po, vir, pf;
  is >> po;
  if(is){
    is >> point.x >> vir >> point.y >> pf;
    assert(po=='(');
    assert(vir==',');
    assert(pf==')');
  }
  return is;
}

