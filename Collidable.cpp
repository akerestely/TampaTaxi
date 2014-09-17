#include "Collidable.h"

Collidable::Collidable(Point center,double width, double height)
	:Object3d(center),width(width),height(height)
{
}

double Collidable::GetTop()
{
	return center.y+height/2;
}
double Collidable::GetBottom()
{
	return center.y-height/2;
}
double Collidable::GetLeft()
{
	return center.x-width/2;
}
double Collidable::GetRight()
{
	return center.x+width/2;
}