#include "Collider.h"

Collider::Collider(Point center, double width, double height)
:Movable(center), Collidable(center, width, height)
{
}

bool Collider::collidesWith(const std::vector<Collidable*> &colliders)
{
	for(int i=0; i<colliders.size(); i++)
		if( GetRight() < colliders[i]->GetLeft() || 
			colliders[i]->GetRight() < GetLeft() ||
			GetTop() < colliders[i]->GetBottom() ||
		    colliders[i]->GetTop() < GetBottom() )
			return true;
	return false;
}

bool Collider::MoveWith(double speed, double angle)
{
	canMove=true;
	Movable::MoveWith(speed,angle);
	if(collidesWith(collidersTemp))
	{
		Movable::MoveWith(speed,angle-180);
		canMove=false;
	}
	return canMove;
}