/*
  INF3105 -- Structures de données et algorithmes
  UQAM | Département d'informatique
  Automne 2014 | TP1 | point.cpp
*/

#include <assert.h>
#include "point.h"

Point::Point(const Point& point)
  : x(point.x), y(point.y)
{
}

Point::Point(const double _x, const double _y)
  : x(_x), y(_y)
{}



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

