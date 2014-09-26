#include "MainMenu.h"
#include "Tools.h"
#include "Controller.h"

MainMenu::MainMenu(Model *model)
	:model(model)
{
	menuPoints.push_back( Point(0.0,0.7,0));
	menuPoints.push_back( Point(0.,0.4,0));
	menuPoints.push_back( Point(0.,0.1,0));
	menuPoints.push_back( Point(0.,-0.2,0));

	controlsPoints.push_back( Point(-0.1,0.7,0));
	controlsPoints.push_back( Point(-0.1,0.6,0));
	controlsPoints.push_back( Point(-0.1,0.5,0));
	controlsPoints.push_back( Point(-0.1,0.4,0));
	controlsPoints.push_back( Point(-0.1,0.3,0));

	controlsText.push_back( "Up : Up arrow,w");
	controlsText.push_back( "Right : Right arrow,d");
	controlsText.push_back( "Down : Down arrow,s");
	controlsText.push_back( "Left : Left arrow,a");
	controlsText.push_back( "Pause : Esc");
	//controlsText.push_back( "camera");
	w=0.3;
	h=0.08;
	locationsMenu=false;
	controlsMenu=false;
	mapMenu=false;
	escPressed=true;
}
void MainMenu::MouseMove(double dx,double dy)
{
	dx=dx/glutGet(GLUT_WINDOW_WIDTH);
	dy=dy/glutGet(GLUT_WINDOW_HEIGHT);
	dx=(dx-0.5)*(2);
	dy=(dy-0.5)*(2)* -1;
	this->xMouse=dx;
	this->yMouse=dy;
}

int MainMenu::getRactangleIndex(double dx,double dy) 
{
	for (int i=0;i<menuPoints.size();i++)
	{
		if(Tools::PointInsideRectangle(Point(dx,dy,0),
			Point(menuPoints[i].x+w,menuPoints[i].y+h,0),
			Point(menuPoints[i].x+w,menuPoints[i].y-h,0),
			Point(menuPoints[i].x-w,menuPoints[i].y-h,0),
			Point(menuPoints[i].x-w,menuPoints[i].y+h,0)))	
				return i;
	}
	return 100;
}
void MainMenu::MouseClicked(int button,int state,double dx,double dy)
{
	dx=dx/glutGet(GLUT_WINDOW_WIDTH);
	dy=dy/glutGet(GLUT_WINDOW_HEIGHT);
	dx=(dx-0.5)*(2);
	dy=(dy-0.5)*(2)* -1;
	
	
	if(state==1) {
		if(!controlsMenu && !locationsMenu && !mapMenu) 
			MainMenuActions(dx,dy);
		else 
		{
			if(controlsMenu) 
			{
				ControlsMenuActions(dx,dy);
			}
			if(locationsMenu) 
			{
				LocationsMenuActions(dx,dy);
			}
			if(mapMenu)
			{
				MapMenuActions(dx,dy);
			}
		}
	
	}
}
void MainMenu::MainMenuActions(double dx,double dy) 
{
	char gameModeString[40] = "640x480";
	Controller *ctrl = Controller::GetInstance();
	switch (getRactangleIndex(dx,dy)) 
	{
	case 0:locationsMenu=true;break;
	case 1:controlsMenu=true;break;
	case 2:mapMenu = true;break;
	case 3:exit(1);break;
	}
}

void MainMenu::MapMenuActions(double dx,double dy) 
{
	Controller *ctrl = Controller::GetInstance();
	switch (getRactangleIndex(dx,dy)) 
	{
	
	case 3:mapMenu=false;break;
	}
}
void MainMenu::ControlsMenuActions(double dx,double dy) 
{
	Controller *ctrl = Controller::GetInstance();
	switch (getRactangleIndex(dx,dy)) 
	{
	case 0:escPressed=!escPressed;break;
	case 1:controlsMenu=false;break;
	case 2:controlsMenu=false;break;
	case 3:controlsMenu=false;break;
	}
}
void MainMenu::LocationsMenuActions(double dx,double dy) 
{
	Controller *ctrl = Controller::GetInstance();
	switch (getRactangleIndex(dx,dy)) 
	{
	//case 0:ctrl->escPressed=!ctrl->escPressed;break;
	//case 1:locationsMenu=false;break;
	//case 2:locationsMenu=false;break;
	case 3:locationsMenu=false;break;
	}
}

void MainMenu::setOrthographicProjection() {
	//switch to projection mode
	glMatrixMode(GL_PROJECTION);
	//save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();
	// reset matrix
	glLoadIdentity();
	// set a 2D orthographic projection
	gluOrtho2D(-1, 1, -1, 1);
	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}
void MainMenu::restorePerspectiveProjection() {
	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();
	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}
void MainMenu::DrawQuad(Point center,double width,double height)
{
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	glTranslated(center.x,center.y,1);
	
	glBegin(GL_QUADS);              
		{
			glColor3f(1,1,1);
			glTexCoord2f(0.0, 0.0);glVertex2f( -width, +height);
			glTexCoord2f(1.0, 0.0);glVertex2f( +width, +height);
			glTexCoord2f(1.0, 1.0);glVertex2f( +width, -height);
			glTexCoord2f(0.0, 1.0);glVertex2f( -width, -height);
		}
	glEnd();
	glPopMatrix();
	restorePerspectiveProjection();
	
}
void MainMenu::renderBitmapString(float x,float y,float z,void *font,char *string) {
  char *c;
  glRasterPos3f(x, y,z);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }

}
void MainMenu::DrawText(Point center,char* s)
{
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	renderBitmapString(center.x,center.y,0,GLUT_BITMAP_HELVETICA_18,s);
	glPopMatrix();
	restorePerspectiveProjection();
}
void MainMenu::DrawBackground()
{
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
	glEnd();
	glDisable(GL_BLEND);

}
void MainMenu::DrawMainMenu() 
{
	Texture tex=Texture::GetInstance();
	glEnable(GL_TEXTURE_2D);
	for(int i=0;i<menuPoints.size();i++) {
		if(getRactangleIndex(xMouse,yMouse)==i){
			glBindTexture(GL_TEXTURE_2D, tex.mainMenu[i]+menuPoints.size());
			DrawQuad(menuPoints[i],w,h);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, tex.mainMenu[i]);
			DrawQuad(menuPoints[i],w,h);
		}
	}
	glDisable(GL_TEXTURE_2D); 
}

void MainMenu::DrawLocationsMenu() 
{
	Texture tex=Texture::GetInstance();
	glEnable(GL_TEXTURE_2D);
	for(int i=0;i<menuPoints.size()-1;i++) {
		if(getRactangleIndex(xMouse,yMouse)==i){
			glBindTexture(GL_TEXTURE_2D, tex.newGameMenu[i+menuPoints.size()-1]);
			DrawQuad(menuPoints[i],w,h);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, tex.newGameMenu[i]);
			DrawQuad(menuPoints[i],w,h);
		}
	}
	if(getRactangleIndex(xMouse,yMouse)==3){
		glBindTexture(GL_TEXTURE_2D, tex.secondMenu[1]);
		DrawQuad(menuPoints[3],w,h);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, tex.secondMenu[0]);
		DrawQuad(menuPoints[3],w,h);
	}
	
	glDisable(GL_TEXTURE_2D); 
}

void MainMenu::DrawMapMenu() 
{
	glLoadIdentity();
	model->GetMap()->GetMinimap()->Draw();
	
	Texture tex=Texture::GetInstance();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.secondMenu[0]);
	
	if(getRactangleIndex(xMouse,yMouse)==3){
		glBindTexture(GL_TEXTURE_2D, tex.secondMenu[1]);
		DrawQuad(menuPoints[3],w,h);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, tex.secondMenu[0]);
		DrawQuad(menuPoints[3],w,h);
	}
	
	glDisable(GL_TEXTURE_2D); 
}
void MainMenu::DrawControlsMenu() 
{
	glColor3f(1,1,1);
	for(int i=0;i<controlsText.size();i++)
	{
		DrawText(controlsPoints[i],controlsText[i]);
	}
	Texture tex=Texture::GetInstance();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.secondMenu[0]);
	DrawQuad(menuPoints[3],w,h);
	if(getRactangleIndex(xMouse,yMouse)==3){
		glBindTexture(GL_TEXTURE_2D, tex.secondMenu[1]);
		DrawQuad(menuPoints[3],w,h);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, tex.secondMenu[0]);
		DrawQuad(menuPoints[3],w,h);
	}
	
	glDisable(GL_TEXTURE_2D); 
}

void MainMenu::Draw() {
	DrawBackground();
	if(!controlsMenu && !locationsMenu && !mapMenu) {
		DrawMainMenu();
	}
	
	if(controlsMenu) 
	{
		DrawControlsMenu();
	}
	if(locationsMenu) 
	{
		DrawLocationsMenu();
	}
	if(mapMenu) 
	{
		DrawMapMenu();
	}
}
void MainMenu::EscPressed() 
{
	if(locationsMenu) {
		locationsMenu=false;
		return;
	}
	if(controlsMenu)
	{
		controlsMenu=false;
		return;
	}
	if(mapMenu)
	{
		mapMenu=false;
		return;
	}
	escPressed= !escPressed;
}
bool MainMenu::GetEscPressed() 
{
	return this->escPressed;
}
bool MainMenu::GetMapMenu() 
{
	return this->mapMenu;
}
MainMenu::~MainMenu(void)
{
}
