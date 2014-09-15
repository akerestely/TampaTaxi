#include "Texture.h"
#include "Win.h"
#define	DOORWIDTH 1.5
#define DOORHEIGHT 4

Win::Win(Point center)
     :Drawable(center)
{
	this->win=false;
	dx = 0;
}

Win::~Win(void)
{

}

void Win::SetWin(bool win){
	this->win=win;
}

void Win::Draw(){

	Texture tex=Texture::GetInstance();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex.winTex);
	glPushMatrix();
	glRotated(10, 0, 1, 0);
	glTranslatef(center.x,center.y,center.z);
	
	if(win==true && dx<=DOORWIDTH){
		dx+=0.01;
	}
	if(win == false && dx > 0)
		dx -= 0.01;
	
	//Win Chipmunk
	if(win==true || dx > 0)
	{
		glPushMatrix();
		glTranslated(0, 0, -0.01);
		glBegin(GL_QUADS);  
		glTexCoord2f(0.0,0.0);
		glVertex3f(-DOORWIDTH, -DOORHEIGHT/2, 0);
		glTexCoord2f(1.0,0.0);
		glVertex3f(DOORWIDTH, -DOORHEIGHT/2,0);
		glTexCoord2f(1.0,1.0);
		glVertex3f(DOORWIDTH, DOORHEIGHT/2,  0);
		glTexCoord2f(0.0,1.0);
		glVertex3f(-DOORWIDTH, DOORHEIGHT/2,  0);
		glEnd();
		glPopMatrix();
	}
	
	//begin drawing the doors
	tex=Texture::GetInstance();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex.doorTex);

	//left static door
	glPushMatrix();
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0);
	glVertex3f(-2*DOORWIDTH, -DOORHEIGHT/2, 0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(-DOORWIDTH, -DOORHEIGHT/2,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(-DOORWIDTH, DOORHEIGHT/2,  0);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-2*DOORWIDTH, DOORHEIGHT/2,  0);
	glEnd();
	glPopMatrix();
	
	//left moving door
	glPushMatrix();
	glTranslatef(-dx, 0, 0.01);
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0);
	glVertex3f(-DOORWIDTH, -DOORHEIGHT/2, 0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(0, -DOORHEIGHT/2,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(0, DOORHEIGHT/2,  0);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-DOORWIDTH, DOORHEIGHT/2,  0);
	glEnd();
	glPopMatrix();
	
	//right moving door
	glPushMatrix();
	glTranslatef(dx, 0, 0.01);
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0);
	glVertex3f(0, -DOORHEIGHT/2, 0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(DOORWIDTH, -DOORHEIGHT/2,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(DOORWIDTH, DOORHEIGHT/2,  0);
	glTexCoord2f(0.0,1.0);
	glVertex3f(0, DOORHEIGHT/2,  0);
	glEnd();
	glPopMatrix();

	//right static door
	glPushMatrix();
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0);
	glVertex3f(DOORWIDTH, -DOORHEIGHT/2, 0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(2*DOORWIDTH, -DOORHEIGHT/2,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(2*DOORWIDTH, DOORHEIGHT/2,  0);
	glTexCoord2f(0.0,1.0);
	glVertex3f(DOORWIDTH, DOORHEIGHT/2,  0);
	glEnd();
	glPopMatrix();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

