#pragma once
#include <vector>
#include "Point.h"
#include "Texture.h"
#include "Minimap.h"
#include "Model.h"

class MainMenu
{
	Model *model;
	bool escPressed;
	bool locationsMenu,controlsMenu,mainMenu,mapMenu;
	double xMouse, yMouse;
	double w,h;

	GLuint newGameButton;
	std::vector<Point> menuPoints;
	std::vector<Point> controlsPoints;
	std::vector<char*> controlsText;

	void DrawQuad(Point center,double width,double height) ;
	void setOrthographicProjection();
	void restorePerspectiveProjection();
	Point ConvertFromMousePoint (Point point);
	Point ConvertToMousePoint (Point point);
	int getRactangleIndex(double dx,double dy) ;

	void MainMenuActions(double dx,double dy); 
	void ControlsMenuActions(double dx,double dy) ;
	void LocationsMenuActions(double dx,double dy) ;
	void MapMenuActions(double dx,double dy) ;

	void DrawMainMenu();
	void DrawBackground();
	void DrawControlsMenu();
	void DrawLocationsMenu();
	void DrawMapMenu();
	void renderBitmapString(float x,float y,float z,void *font,char *string);
	void DrawText(Point center,char* s);

public:

	MainMenu(Model *model);
	~MainMenu(void);

	bool GetEscPressed();
	bool GetMapMenu();
	void EscPressed();
	void MouseMove(double dx,double dy);
	void MouseClicked(int button,int state,double dx,double dy);
	void Draw() ;
};
