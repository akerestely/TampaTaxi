#pragma once
#include "Collidable.h"
#include<vector>
class Movable : public Collidable
{
protected:
	bool canMove;
public:
	std::vector<Collidable*> *colliders;
	Movable();
	Movable(Point center,double width, double height);
	bool CollidesWith();
	bool MoveWith(double speed);
};
