#include "Animable.h"

Animable::Animable(Point center)
	:Movable(center)
{
}
bool Animable::MoveWith(double speed, double angle)
{
	if(canMove)
		return Movable::MoveWith(speed,angle);
	return false;
}