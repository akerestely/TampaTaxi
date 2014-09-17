#include "Movable.h"
#include "math.h"

Movable::Movable(Point center)
	:Object3d(center)
{
	canMove=true;
}
bool Movable::MoveWith(double speed, double angle)
{
	angle*=PI/180;
	center.x=center.x+speed*cos(angle);
	center.z=center.z+speed*sin(angle);
	return true;
}

