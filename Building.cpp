#include "Tools.h"
#include<ctime>
#include "cmath"
#include "Building.h"
#include "Texture.h"
#include "CameraSpectator.h"


Building::Building(Point center,double size, int type,double angleOfRotation)
:Drawable(center),size(size),type(type),angleOfRotation(angleOfRotation)
{
	
	int mytime = rand()%5;
	Texture tex=Texture::GetInstance();
	myTexture = tex.textures[mytime];
}


void Building::Draw() 
{
	switch(this->type) {
		case 1:
			{
				double w=0.25,h=3.1; 
				model1(w,h);
				break;
			} 
		case 2:
			{
				double w=0.25,h=0.75; 
				model1(w,h);
				break;
			} 
		case 3:
			{
				double w=0.45,h=0.25; 

				model1(w,h);
				break;

			} 
	}
}
void Building::model1(double w, double h) 
{
	length = w;
	width = w;
	height = h;
	if(!mode)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, myTexture);	
		glPushMatrix();
		glTranslatef(this->center.x, this->center.y+h*size, this->center.z);
		glRotated(this->angleOfRotation,0, 1, 0);
		
		glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
		{
			// Top face (y = 1.0f)
			// Define vertices in counter-clockwise (CCW) order with normal pointing out
			glVertex3f( w*size, h*size, -w*size);
			glVertex3f( -w*size, h*size, -w*size);
			glVertex3f( -w*size, h*size, w*size);
			glVertex3f( w*size, h*size, w*size);
		}
		glEnd();
		glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
		{
			// Bottom face (y = -1.0f)
			glVertex3f( w*size, -h*size, w*size);
			glVertex3f( -w*size, -h*size, w*size);
			glVertex3f( -w*size, -h*size, -w*size);
			glVertex3f( w*size, -h*size, -w*size);
		}
		glEnd();
		glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
		{
			// Front face  (z = 1.0f)
			glTexCoord2f(2.0, 2.0); glVertex3f( w*size, h*size, w*size);
			glTexCoord2f(0.0, 2.0); glVertex3f( -w*size, h*size, w*size);
			glTexCoord2f(0.0, 0.0); glVertex3f( -w*size, -h*size, w*size);
			glTexCoord2f(2.0, 0.0); glVertex3f( w*size, -h*size, w*size);
		}
		glEnd();
		glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
		{
			// Right face (x = 1.0f)
			glTexCoord2f(0.0, 2.0); glVertex3f( w*size, h*size, -w*size);
			glTexCoord2f(2.0, 2.0); glVertex3f( w*size, h*size, w*size);
			glTexCoord2f(2.0, 0.0); glVertex3f( w*size, -h*size, w*size);
			glTexCoord2f(0.0, 0.0); glVertex3f( w*size, -h*size, -w*size);
		}
		glEnd();
		glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
		{
			// Left face (x = -1.0f)
			glTexCoord2f(0.0, 2.0); glVertex3f( -w*size, h*size, w*size);
			glTexCoord2f(2.0, 2.0); glVertex3f( -w*size, h*size, -w*size);
			glTexCoord2f(2.0, 0.0); glVertex3f( -w*size, -h*size, -w*size);
			glTexCoord2f(0.0, 0.0); glVertex3f( -w*size, -h*size, w*size);
		}
		glEnd();

	//	glBindTexture(GL_TEXTURE_2D, tex.wallTex2);
		glBegin(GL_QUADS);
		{
			// Back face (z = -1.0f)
			glTexCoord2f(2.0, 0.0); glVertex3f( w*size, -h*size, -w*size);
			glTexCoord2f(0.0, 0.0); glVertex3f( -w*size, -h*size, -w*size);
			glTexCoord2f(0.0, 2.0); glVertex3f( -w*size, h*size, -w*size);
			glTexCoord2f(2.0, 2.0); glVertex3f(w*size, h*size, -w*size);
		}
		glEnd();  // End of drawing color-cube
		glPopMatrix();
		glDisable(GL_TEXTURE_2D); 
	}
}

void Building::SwitchMode(Point p,double rotY)
{

	rotY += 90;
	Point A = Point(center.x + width*size, 0, center.z + length*size);
	Point D = Point(center.x - width*size, 0, center.z + length*size);
	Point C = Point(center.x - width*size, 0, center.z - length*size);
	Point B = Point(center.x + width*size, 0, center.z - length*size);

	double cosAlfa = cos(rotY*PI / 180);
	double sinAlfa = sin(rotY*PI / 180);
	for (double r = 1; r < 15; r++)
	{
		Point M(p.x,0,p.z);
		M.x += r*cosAlfa;
		M.z += r*sinAlfa;
		SF3dVector AP(A, M), AB(A, B), AD(A, D);
		if (((0 < (AP*AB)) && ((AP*AB) < (AB*AB))) &&
			((0 < (AP*AD)) && ((AP*AD) < (AD*AD))))
		{
			mode = true;
			break;
		}
		else
			mode = false;
	}
}

Building::~Building(void)
{
}
