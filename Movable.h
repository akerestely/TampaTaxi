#pragma once
#include "Object3d.h"

class Movable : public Object3d
{
protected:
	bool canMove;
public:
	Movable(Point center);
	virtual bool MoveWith(double speed, double angle);
};
