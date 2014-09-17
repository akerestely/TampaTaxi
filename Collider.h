#pragma once
#include <vector>
#include "Movable.h"
#include "Collidable.h"

class Collider : public Movable, private Collidable
{
	bool collidesWith(const std::vector<Collidable*> &colliders);
public:
	//temp
	std::vector<Collidable*> collidersTemp;
	//temp
	Collider(Point center, double width, double height);
	virtual bool MoveWith(double speed, double angle) override;
};
