#pragma once
#include "Point.h"
class Object3d
{
protected:
	Point center;
	double angle;
public:
	Object3d(Point center);
	virtual void IncrementAngle(double deltaAngle);
	virtual void SetAngle(double angle);
	void setCenter(Point center);
	Point GetCenter();
	~Object3d(void);
};
