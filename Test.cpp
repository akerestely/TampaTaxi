#include "Test.h"
#include "glut.h"

Test::Test(Point center, double width,double height)
	:Movable(center, width, height)
{
}

void Test::Draw()
{
	
	glPushMatrix();
	
	//glTranslatef(-Object3d::center.x,Object3d::center.y,-Object3d::center.z);
	//glRotatef(Object3d::angle*180/PI,0.0,1.0,0.0);
	glBegin(GL_QUADS);
	glVertex3f(GetTopLeft().x,0.0,GetTopLeft().z);
	glVertex3f(GetTopRight().x,0.0,GetTopRight().z);
	glVertex3f(GetBottomRight().x,0.0,GetBottomRight().z);
	glVertex3f(GetBottomLeft().x,0.0,GetBottomLeft().z);
	glEnd();
	glPopMatrix();
	
}
Test::~Test(void)
{
}