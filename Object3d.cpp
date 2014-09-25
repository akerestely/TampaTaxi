#include "Object3d.h"

Object3d::Object3d(Point center):center(center)
	
{
	angle=0*PI/180;
}

void Object3d::IncrementAngle(double deltaAngle)
{
	angle+=deltaAngle*PI/180;
}

void Object3d::SetAngle(double angle)
{
	this->angle=angle*PI/180;
}

void Object3d::setCenter(Point center)
{
	this->center=center;
}
Point Object3d::GetCenter()
{
	return center;
}

Object3d::~Object3d(void)
{
}