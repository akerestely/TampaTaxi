#include "MainMenu.h"

MainMenu::MainMenu(void)
{
}

void MainMenu::Draw() {
	//DrawText(Point(0.,0.2,-1),newGame);
	double w=0.2,h=0.03;
	 glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);              
		{
			glColor4f(0,0,0,0.8);
			glVertex3f( -1, -1, -1);
			glVertex3f( 1, -1, -1);
			glVertex3f( 1, 1, -1);
			glVertex3f( -1, 1, -1);
		}
		 glDisable(GL_BLEND);
	menuPoints.push_back( Point(0.,0.2,-1));
	menuPoints.push_back( Point(0.,0.10,-1));
	menuPoints.push_back( Point(0.,0.0,-1));
	menuPoints.push_back( Point(0.,-0.10,-1));
	//glTranslated(menuPoints[i].x,menuPoints[i].y,menuPoints[i].z);
	
	//glDisable(GL_TEXTURE_2D);
	glColor3f(1.,1.,1);
	for(int i=0;i<menuPoints.size();i++) {
		glPushMatrix();
		glTranslated(menuPoints[i].x,menuPoints[i].y,-1);
		glBegin(GL_QUADS);              
		{
			glVertex3f( -w, -h, 0);
			glVertex3f( -w, h,  0);
			glVertex3f( w, h, 0);
			glVertex3f( w, -h, 0);
		}
		glEnd();
		glPopMatrix();
	}

	
}
MainMenu::~MainMenu(void)
{
}
