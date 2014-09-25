#pragma once
#include "vector"
#include "Collidable.h"
class Movable : public Collidable
{
protected:
	SF3dVector viewDir;
	void computeViewDir();
public:
	std::vector<Collidable*> *colliders;
	Movable(Point center,double width, double height);
	virtual void IncrementAngle(double deltaAngle);
	virtual void SetAngle(double angle);
	void SetViewDir(SF3dVector normalizedVector);
	bool CollidesWith();
	bool MoveWith(double speed);	
	bool MoveWith(SF3dVector speedVector);
};
