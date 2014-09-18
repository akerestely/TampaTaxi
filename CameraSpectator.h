#pragma once
#include "Point.h"
#include <glut.h>		// Need to include it here because the GL* types are required
#define PIdiv180 0.01745329251

/////////////////////////////////
//Note: All angles in degrees  //
/////////////////////////////////

struct SF3dVector  //Float 3d-vect, normally used
{
	GLfloat x,y,z;
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
};
struct SF2dVector
{
	GLfloat x,y;
};

class CCamera
{
private:
	SF3dVector Position;
	SF3dVector ViewDir;		/*Not used for rendering the camera, but for "moveforwards"
							So it is not necessary to "actualize" it always. It is only
							actualized when ViewDirChanged is true and moveforwards is called*/
	bool ViewDirChanged;
	GLfloat RotatedX, RotatedY, RotatedZ;	
	void GetViewDir ( void );
public:
	CCamera();				//inits the values (Position: (0|0|0) Target: (0|0|-1) )
	void Render ( void );	//executes some glRotates and a glTranslate command
							//Note: You should call glLoadIdentity before using Render
	void Move ( SF3dVector Direction );
	void RotateX ( GLfloat Angle );
	void RotateY ( GLfloat Angle );
	void RotateZ ( GLfloat Angle );
	void RotateXYZ ( SF3dVector Angles );
	void MoveZ ( GLfloat Distance );
	void MoveX ( GLfloat Distance );
	Point GetPosition();
	double GetRotY();
};


SF3dVector F3dVector ( GLfloat x, GLfloat y, GLfloat z );
SF3dVector AddF3dVectors ( SF3dVector * u, SF3dVector * v);
void AddF3dVectorToVector ( SF3dVector * Dst, SF3dVector * V2);
