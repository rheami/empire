
#if !defined(__SEGMENT_H__)
#define __SEGMENT_H__

#include "point.h"


class Segment
{
public:
	Segment(const Point& _A, const Point& _B);
	~Segment();
	double distance(const Segment& other);
private:
	Point A;
	Point B;
};

#endif

