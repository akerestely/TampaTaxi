#pragma once
#include <cmath>
#define PI 3.14159265359
#define PIdiv180 0.01745329251

class Point
{
public:
	double x,y,z;
	Point(double x=0,double y=0,double z=0);
	Point operator + (const Point &p);
	Point operator - (const Point &p);
};

struct SF3dVector
{
	double x,y,z;

	SF3dVector(double x = 0, double y = 0, double z = 0)
	{
		this->x=x;
		this->y = y;
		this->z = z;
	}
	SF3dVector(Point a, Point b)
	{
		x = b.x - a.x;
		y = b.y - a.y;
		z = b.z - a.z;
	}
	// Scalar product of two vectors
	double operator*(const SF3dVector &v)
	{
		return x*v.x + y*v.y+z*v.z;
	}
	SF3dVector operator*(double scalar)
	{
		return SF3dVector(x*scalar , y*scalar, z*scalar);
	}
	SF3dVector operator/(double scalar)
	{
		return SF3dVector(x/scalar , y/scalar, z/scalar);
	}
	SF3dVector operator+(const SF3dVector &v)
	{
		return SF3dVector(x+v.x, y+v.y,z+v.z);
	}
	SF3dVector operator+=(const SF3dVector &v)
	{
		x+=v.x;
		y+=v.y;
		z+=v.z;
		return *this;
	}
	double GetMagnitude()
	{
		return sqrt(x*x+y*y+z*z);
	}
	SF3dVector GetNormalized()
	{
		return (*this)/GetMagnitude();
	}
	Point ToPoint()
	{
		return Point(x,y,z);
	}
};