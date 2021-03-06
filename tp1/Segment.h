
#if !defined(__SEGMENT_H__)
#define __SEGMENT_H__

#include "point.h"


class Segment
{
public:
	Segment(const Point& _debut, const Point& _fin);
	~Segment();
	double distance(const Segment& other) const;

	double distancePointSegment(const Point& pointA, const Segment& segmentCD) const;
	Point getProjection(const Point& point) const;

	friend std::ostream& operator << (std::ostream& os, const Segment& segement) {
		os << "(" << segement.debut << "," << segement.fin << ")";
		return os;
	}
private:
	Point debut;
	Point fin;
};

#endif

