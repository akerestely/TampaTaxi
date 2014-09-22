#include "DebugWindow.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Point.h"
#include <glut.h>

DebugWindow::DebugWindow(Model *model)
	:model(model)
{
	this->frame=0;
	this->timebase=0;
	//Texture tex=Texture::GetInstance();
	//newGameButton = tex.newGameButton;
}

void DebugWindow::renderBitmapString(float x,float y,float z,void *font,char *string) {
  char *c;
  glRasterPos3f(x, y,z);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }

}
void DebugWindow::setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, 640, 480, 0);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}
void DebugWindow::restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void DebugWindow::DrawFPS (Point fpsPosition) {
	frame++;
	timeFrame=glutGet(GLUT_ELAPSED_TIME);

	if (timeFrame - timebase > 10) {
		sprintf(textFrame,"FPS: %4.2f",
			frame*1000.0/(timeFrame-timebase));
	 	timebase = timeFrame;
		frame = 0;
	}
	DrawText(fpsPosition,textFrame);
}
void DebugWindow::DrawText(Point center,char* s)
{
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	renderBitmapString(center.x,center.y,0,GLUT_BITMAP_HELVETICA_18,s);
	glPopMatrix();
	restorePerspectiveProjection();
}
void DebugWindow::DrawCameraPosition(Point textPosition) 
{
	Point camPosition = model->GetCamera().GetPosition();	
	sprintf(textCam,"Camera position: %4.2f, %4.2f, %4.2f",
		camPosition.x,camPosition.y,camPosition.z);
	DrawText(textPosition,textCam);
}
void DebugWindow::Draw() 
{
	glColor3f(1,1,1);
	DrawFPS(Point(5,20,0));
	DrawCameraPosition(Point(5,30,0));
}
DebugWindow::~DebugWindow(void)
{
}
