#pragma once
#include "vector"
#include "Collidable.h"
class Movable : public Collidable
{
protected:
	bool canMove;
public:
	std::vector<Collidable*> *colliders;
	Movable(Point center,double width, double height);
	bool CollidesWith();
	bool MoveWith(double speed);
};
