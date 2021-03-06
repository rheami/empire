#include "segment.h"
#include "point.h"


Segment::Segment(const Point& _debut, const Point& _fin)
{
	debut = _debut;
	fin = _fin;
}


Segment::~Segment()
{
}

Point Segment::getProjection(const  Point& point) const {
    Point CA = point - debut;
    Point CD = fin - debut;
    double num = CA * CD;
    double denum = CD * CD;
    double ratio = num / denum;
    ratio = ratio > 1 ? 1 : ratio;
    ratio = ratio < 0 ? 0 : ratio;
    Point projection = CD*ratio; // note: ne pas faire ratio * CD
    Point E = debut + projection;
    return E;
}

double Segment::distancePointSegment(const Point& pointA, const Segment& segmentCD) const {
    Point pointE = segmentCD.getProjection(pointA);
    double distance = pointA.distance(pointE);
    //std::cout << pointA << segmentCD << distance << std::endl;
    return distance;
}
//
double Segment::distance(const Segment& other) const  {
	double distance = distancePointSegment(debut, other);
	distance = min(distancePointSegment(fin, other), distance);
	distance = min(distancePointSegment(other.debut, *this), distance);
	distance = min(distancePointSegment(other.fin, *this), distance);

  return distance;
}
