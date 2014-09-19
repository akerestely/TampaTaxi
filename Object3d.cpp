#include "Object3d.h"

Object3d::Object3d(Point center):center(center)
	
{
	angle=0;
}

void Object3d::setAngle(double angle)
{
	this->angle+=angle*PI/180;
}
Object3d::Object3d()
{
}
Object3d::~Object3d(void)
{
}

Point Object3d::GetCenter()
{
	return center;
}