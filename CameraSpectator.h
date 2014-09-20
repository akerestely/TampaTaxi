#pragma once
#include "Point.h"

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
