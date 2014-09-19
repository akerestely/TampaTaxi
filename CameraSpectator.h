#pragma once
#include "Point.h"
#define PIdiv180 0.01745329251

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
};

class CCamera
{
private:
	SF3dVector Position;
	/*Not used for rendering the camera, but for "moveforwards".*/
	SF3dVector ViewDir;
	double RotatedX, RotatedY, RotatedZ;	
	void ComputeViewDir ( void );
public:
	CCamera();				//inits the values (Position: (0|0|0) Target: (0|0|-1) )
	void Render ( void );	//executes some glRotates and a glTranslate command
							//Note: You should call glLoadIdentity before using Render
	void Move ( SF3dVector Direction );
	void RotateX ( double Angle );
	void RotateY ( double Angle );
	void RotateZ ( double Angle );
	void RotateXYZ ( SF3dVector Angles );
	SF3dVector& MoveX ( double Distance );
	SF3dVector& MoveZ ( double Distance );
	Point GetPosition();
	double GetRotY();
};
