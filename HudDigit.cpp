#include "HudDigit.h"
#include<glut.h>
HudDigit::HudDigit()
{
}
HudDigit::HudDigit(Point center,int digit,double gaugeRadius):Drawable(center),digit(digit),
gaugeRadius(gaugeRadius)
{
}

void HudDigit::Draw()
{
	int digitPlus=digit+1;
	
	glPushMatrix();
	glTranslatef(center.x,center.y,center.z);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,Texture::GetInstance().hudNumbers);
	glBegin(GL_QUADS);
	glTexCoord2d(0.1*digit, 1);glVertex3f(-gaugeRadius/10,-gaugeRadius/10,0.);
	glTexCoord2d(0.1*digitPlus,1);glVertex3f(gaugeRadius/10,-gaugeRadius/10,0.);
	glTexCoord2d(0.1*digitPlus,0);glVertex3f(gaugeRadius/10,gaugeRadius/10,0.);
	glTexCoord2d(0.1*digit,0);glVertex3f(-gaugeRadius/10,gaugeRadius/10,0.);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	
}
void HudDigit::setDigit(int digit)
{
	this->digit=digit;
}
HudDigit::~HudDigit(void)
{
}
