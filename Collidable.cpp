#include "Collidable.h"
#include "math.h"

Collidable::Collidable(Point center,double width, double height)
	:Object3d(center),width(width),height(height)
{
}

Point Collidable::GetTopLeft()
{
	double x0=center.x;
	double z0=center.z;
	double x=center.x-width/2;
	double z=center.z+height/2;
	
	if(angle==0)
		return Point(x,center.y, z);
	double newX=x0+(x-x0)*cos(angle)+(z-z0)*sin(angle);
 	double newZ=z0-(x-x0)*sin(angle)+(z-z0)*cos(angle);
	return Point(newX, center.y, newZ);
}

Point Collidable::GetTopRight()
{
	double x0=center.x;
	double z0=center.z;
	double x=center.x+width/2;
	double z=center.z+height/2;
	if(angle==0)
		return Point(x,center.y, z);
	double newX=x0+(x-x0)*cos(angle)+(z-z0)*sin(angle);
	double newZ=z0-(x-x0)*sin(angle)+(z-z0)*cos(angle);
	return Point(newX, center.y, newZ);
}
Point Collidable::GetBottomLeft()
{
	double x0=center.x;
	double z0=center.z;
	double x=center.x-width/2;
	double z=center.z-height/2;
	if(angle==0)
		return Point(x,center.y, z);
	double newX=x0+(x-x0)*cos(angle)+(z-z0)*sin(angle);
	double newZ=z0-(x-x0)*sin(angle)+(z-z0)*cos(angle);
	return Point(newX, center.y, newZ);
}
Point Collidable::GetBottomRight()
{
	double x0=center.x;
	double z0=center.z;
	double x=center.x+width/2;
	double z=center.z-height/2;
	if(angle==0)
		return Point(x,center.y, z);
	double newX=x0+(x-x0)*cos(angle)+(z-z0)*sin(angle);
	double newZ=z0-(x-x0)*sin(angle)+(z-z0)*cos(angle);
	return Point(newX, center.y, newZ);
}