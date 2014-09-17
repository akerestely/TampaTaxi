#pragma once
#include "Object3d.h"
#include <iostream>

class Collidable : private Object3d
{
protected:
	double width, height;
public:
	double GetTop();
	double GetBottom();
	double GetLeft();
	double GetRight();
	Collidable(Point center, double width, double height);
};
