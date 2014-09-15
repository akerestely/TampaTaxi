#include "Hud.h"

#include<cmath>
Hud::Hud()
{
}

Hud::Hud(Point center)
{	
	this->hudTex=Texture::GetInstance().hudText;
}

void Hud::Draw()
{
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,Texture::GetInstance().hudText);
	double r=0.5;
	glPushMatrix();
	glScaled(0.15,0.15,1);
	glTranslatef(2.7,-2.0,0);
	glTranslatef(center.x,center.y,-1.0);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.5,0.5);glVertex3f( 0,0,0. ); 
	for(double t = 0; t<=360;t+=1)
	{	
		glTexCoord2d(r * cos(2 * PI - t * PI / 180) + 0.5, r * sin(2 * PI - t * PI / 180) + 0.5);
		glVertex3d(r * cos(t * PI / 180),r * sin(t * PI / 180), 0.);
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

Hud::~Hud(void)
{
}
