#include "Point.h"

Point::Point(double x,double y, double z)
	:x(x),y(y),z(z)
{
}

Point Point::operator + (const Point &p)
{
	return Point(x+p.x, y+p.y, z+p.z);
}
Point Point::operator - (const Point &p)
{
	return Point(x-p.x, y-p.y, z-p.z);
}
bool Point::operator == (const Point &p)
{
	return (x == p.x && y == p.y && z == p.z);
}