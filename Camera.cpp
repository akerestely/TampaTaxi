#include "Camera.h"
#include <glut.h>

Camera::Camera()
{
	dx=dz=ry;
}
void Camera::MoveX(double dx)
{
	this->dx-=dx;
}
void Camera::MoveZ(double dz)
{
	this->dz-=dz;
}
void Camera::RotateY(double ry)
{
	this->ry+=ry;
}
void Camera::Render()
{
	glRotatef(ry,0,1,0);
	
	glTranslatef(dx,0,dz);
}
