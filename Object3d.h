#pragma once
#include "Point.h"
class Object3d
{
protected:
	Point center;
	double angle;
public:
	Object3d();
	Object3d(Point center);
	void setAngle(double angle);
	Point GetCenter();
	~Object3d(void);
};
