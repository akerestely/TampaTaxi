#pragma once
#include "Object3d.h"

class Collidable : public Object3d
{
protected:
	double width, height;
public:
	Point GetTopLeft();
	Point GetTopRight();
	Point GetBottomLeft();
	Point GetBottomRight();
	Collidable(Point center, double width, double height);
};
