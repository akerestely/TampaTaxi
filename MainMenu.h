#pragma once
#include <vector>
#include "Point.h"
#include "Texture.h"
class MainMenu
{
public:
	bool locationsMenu,controlsMenu,mainMenu;
	double xMouse, yMouse;
	double w,h;
	MainMenu(void);
	~MainMenu(void);
	GLuint newGameButton;
	std::vector<Point> menuPoints;
	std::vector<Point> controlsPoints;
	std::vector<char*> controlsText;
	void MouseMove(double dx,double dy);
	void MouseClicked(int button,int state,double dx,double dy);
	void Draw() ;
	void DrawQuad(Point center,double width,double height) ;
	void setOrthographicProjection();
	void restorePerspectiveProjection();
	Point ConvertFromMousePoint (Point point);
	Point ConvertToMousePoint (Point point);
	int getRactangleIndex(double dx,double dy) ;
	void MainMenuActions(double dx,double dy); 
	void ControlsMenuActions(double dx,double dy) ;
	void LocationsMenuActions(double dx,double dy) ;
	void DrawMainMenu();
	void DrawBackground();
	void DrawControlsMenu();
	void DrawLocationsMenu();
	void renderBitmapString(float x,float y,float z,void *font,char *string);
	void DrawText(Point center,char* s);
};
