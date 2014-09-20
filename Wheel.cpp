#include "math.h"
#include "Texture.h"
#include "Wheel.h"
#include "glut.h"

Wheel::Wheel(Point center, double r,double w) 
	:Object3d(center), radius(r), width(w), angle(0)
{
	Texture tex = Texture::GetInstance();
	side = tex.wheelSide;
	base = tex.wheelBase;
}

void Wheel::Draw()
{
	glPushMatrix();
	double x, y,tx,ty;
	glRotatef(-90, 0, 1, 0);
	glTranslatef(center.x, center.y + radius, center.z);
	glRotatef(angle+=6, 0, 0,1);

	//base
	glTranslatef(0, 0, -width / 2);
	GLUquadric *qobj = gluNewQuadric();
	gluQuadricTexture(qobj, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, base);
	gluCylinder(qobj, radius, radius, width, 30, 30);
	
	//sides
	glBindTexture(GL_TEXTURE_2D, side);
	glBegin(GL_POLYGON);
	for (double anglew = 0.0f; anglew<361.0f; anglew += 0.5)
	{
		x = cos(anglew)*radius;
		y = sin(anglew)*radius;
		tx = cos(anglew) * 0.5 + 0.5;
		ty = sin(anglew) * 0.5 + 0.5;
		glTexCoord2f(tx, ty); glVertex2f(x, y);
	}
	glEnd();

	glTranslatef(0, 0, +width);
	glBegin(GL_POLYGON);
	for (double anglew = 0.0f; anglew<361.0f; anglew += 0.5)
	{
		x = cos(anglew)*radius;
		y = sin(anglew)*radius;
		tx = cos(anglew) * 0.5 + 0.5;
		ty = sin(anglew) * 0.5 + 0.5;
		glTexCoord2f(tx, ty); glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

Wheel::~Wheel()
{
}
