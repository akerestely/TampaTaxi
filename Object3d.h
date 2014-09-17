#pragma once
#include "Point.h"

class Object3d
{
protected:
	Point center;
public:
	Object3d(Point center);
	Point GetCenter();
	~Object3d(void);
};
