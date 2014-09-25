
#if !defined(__SEGMENT_H__)
#define __SEGMENT_H__

#include "point.h"


class Segment
{
public:
	Segment(const Point& _debut, const Point& _fin);
	~Segment();
	double distance(const Segment& other);

    double distancePointSegment(Point& pointA ,const Segment& segmentCD);
    Point getProjection(Point& point) const;

private:
	Point debut;
	Point fin;
};

#endif

