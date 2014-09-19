#include "math.h"
#include "CameraSpectator.h"
#include <glut.h>

CCamera::CCamera()
{
	//Init with standard OGL values:
	Position = SF3dVector (	0.0, 1.0, 0.0);
	ViewDir = SF3dVector ( 0.0, 0.0, -1.0);
	//Only to be sure:
	RotatedX = RotatedY = RotatedZ = 0.0;
}

void CCamera::ComputeViewDir( void )
{
	SF3dVector Step1, Step2;
	//Rotate around Y-axis:
	Step1.x = cos( (RotatedY + 90.0) * PIdiv180);
	Step1.z = -sin( (RotatedY + 90.0) * PIdiv180);
	ViewDir = Step1;
	////Rotate around X-axis:
	//double cosX = cos (RotatedX * PIdiv180);
	//Step2.x = Step1.x * cosX;
	//Step2.z = Step1.z * cosX;
	//Step2.y = sin(RotatedX * PIdiv180);
	////Rotation around Z-axis not yet implemented, so:
	//ViewDir = Step2;
}

void CCamera::Render( void )
{
	glTranslated( 0.0, 0.0, -3.0 );
	glRotated(-RotatedX , 1.0, 0.0, 0.0);
	glRotated(-RotatedY , 0.0, 1.0, 0.0);
	glRotated(-RotatedZ , 0.0, 0.0, 1.0);
	glTranslatef( -Position.x, -Position.y, -Position.z );
}

void CCamera::Move (SF3dVector Direction)
{
	Position+=Direction;
}

void CCamera::RotateX (double Angle)
{
	RotatedX += Angle;
}

void CCamera::RotateY (double Angle)
{
	RotatedY += Angle;
}

SF3dVector& CCamera::MoveX ( double Distance )
{
	ComputeViewDir();
	SF3dVector MoveVector(-ViewDir.x * -Distance, 0 , ViewDir.z * -Distance);
	Position += MoveVector;
	return MoveVector;
}

SF3dVector& CCamera::MoveZ( double Distance )
{
	ComputeViewDir();
	SF3dVector MoveVector=ViewDir * -Distance;
	Position += MoveVector;
	return MoveVector;
}

Point CCamera::GetPosition()
{
	return Point(Position.x, Position.y, Position.z);
}

double CCamera::GetRotY()
{
	return RotatedY;
}