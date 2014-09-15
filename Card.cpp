#include "Texture.h"
#include "Card.h"
#define CARD_WIDTH 1.5
#define CARD_HEIGHT 2.5

Card::Card(Point center,bool isMiniCard)
:Drawable(center)
{
	angle=0.;
	this->isMiniCard=isMiniCard;
}

Card::~Card(void)
{
}

void Card::Draw()
{
	if(isMiniCard)
		DrawMiniCard();
	else
		DrawBigCard();
	
}

void Card::DrawBigCard()
{
	angle+=1;
	Texture tex=Texture::GetInstance();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex.cardTex[0]);
	glPushMatrix();
	glTranslatef(center.x,center.y,center.z);
	glRotatef(angle, 0., center.y, 0.);
	

	glBegin(GL_QUADS);  
	glColor3f(1.0f, 1.0f, 1.0f);  
	glTexCoord2f(0.0,0.0);
	glVertex3f(-CARD_WIDTH/2, center.y,0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(+CARD_WIDTH/2, center.y,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(+CARD_WIDTH/2, center.y+CARD_HEIGHT,  0);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-CARD_WIDTH/2, center.y+CARD_HEIGHT,  0);
	glEnd();
	
	double distanceToGroundUnit=center.y/11;
	GLUquadricObj *quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GL_TRUE); 
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.cardTex[1]);

	glPushMatrix();
	glRotatef(-angle*4, 0., center.y, 0.);
	glTranslatef(0.,8*distanceToGroundUnit,0.);

	gluSphere(quadric, 0.20, 30, 10);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(angle*3, 0., center.y, 0.);
	glTranslatef(0.,4*distanceToGroundUnit,0.);
	gluSphere(quadric, 0.10, 30, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.,1*distanceToGroundUnit,0.);
	gluSphere(quadric, 0.05, 30, 10);
	glPopMatrix();

	glPopMatrix();
	//glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


void Card::DrawMiniCard()
{

 angle+=1;
 Texture tex=Texture::GetInstance();
 glMatrixMode(GL_MODELVIEW);
 glEnable(GL_TEXTURE_2D);

 glBindTexture(GL_TEXTURE_2D, tex.cardTex[0]);
 glPushMatrix();
 glTranslatef(center.x,center.y,center.z);
 glScaled(0.075,0.075,0.075);
 glRotatef(angle, 0., center.y, 0.);

 glBegin(GL_QUADS);  
 glColor3f(1.0f, 1.0f, 1.0f);  
 glTexCoord2f(0.0,0.0);
 glVertex3f(-CARD_WIDTH/2, center.y,0);
 glTexCoord2f(1.0,0.0);
 glVertex3f(+CARD_WIDTH/2, center.y,0);
 glTexCoord2f(1.0,1.0);
 glVertex3f(+CARD_WIDTH/2, (center.y+CARD_HEIGHT),  0);
 glTexCoord2f(0.0,1.0);
 glVertex3f(-CARD_WIDTH/2, (center.y+CARD_HEIGHT),  0);
 glEnd();

 double distanceToGroundUnit=center.y/11;
 GLUquadricObj *quadric=gluNewQuadric();
 gluQuadricNormals(quadric, GLU_SMOOTH);
 gluQuadricTexture(quadric, GL_TRUE); 

 glEnable(GL_TEXTURE_2D);
 glBindTexture(GL_TEXTURE_2D, tex.cardTex[1]);

 glPushMatrix();
 glRotatef(-angle*4, 0., center.y, 0.);
 glTranslatef(0.,8*distanceToGroundUnit,0.);

 gluSphere(quadric, 0.20, 30, 10);
 glPopMatrix();

 glPushMatrix();
 glRotatef(angle*3, 0., center.y, 0.);
 glTranslatef(0.,4*distanceToGroundUnit,0.);
 gluSphere(quadric, 0.10, 30, 10);
 glPopMatrix();

 glPushMatrix();
 glTranslatef(0.,1*distanceToGroundUnit,0.);
 gluSphere(quadric, 0.05, 30, 10);
 glPopMatrix();

 glPopMatrix();


 glDisable(GL_TEXTURE_2D);

}
