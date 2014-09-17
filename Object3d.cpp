#include "Object3d.h"

Object3d::Object3d(Point center)
	:center(center)
{
}

Object3d::~Object3d(void)
{
}

Point Object3d::GetCenter()
{
	return center;
}