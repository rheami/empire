#include "Segment.h"
#include "Point.h"


Segment::Segment(const Point& _debut, const Point& _fin)
{
	debut = _debut;
	fin = _fin;
}


Segment::~Segment()
{
}

Point Segment::getProjection(Point& point) const {
    Point CA = point - debut;
    Point CD = fin - debut;
    double num = CA * CD;
    double denum = CD * CD;
    double ratio = num / denum;
    ratio = ratio > 1 ? 1 : ratio;
    Point projection = CD*ratio; // note: ne pas faire ratio * CD
    Point E = debut + projection;
    return E;
}

double Segment::distancePointSegment(Point& pointA , const Segment& segmentCD) {
    Point pointE = segmentCD.getProjection(pointA);
    double distance = pointA.distance(pointE);
    cout << pointA << segmentCD << distance << endl;
    return distance;
}
//
double Segment::distance(const Segment& other){
  double distance = distancePointSegment(debut, other);

  return distance;
}
