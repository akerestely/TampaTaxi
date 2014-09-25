#pragma once
#include "Model.h"
#include "Scene.h"
#include "DebugWindow.h"
#include "MainMenu.h"
#include "Hud.h"
#include <glut.h>

class Controller
{
	char* lastWayName;
	std::vector<char*> waysNames;
	bool escPressed,debugWindowPressed;
	bool up,down,left,right,climbUp,climbDown,rotLeft,rotRight,jump;
	int windowWidth,windowHeight;
	Model *model;

	Scene* scene;
	Hud* hud;
	DebugWindow* debugWindow;
	MainMenu* mainMenu;
	Controller(void);
public:
	 bool escPressed;
	static Controller* GetInstance()
	{
		static Controller instance;
		return &instance;
	}

	static void RenderDisplay();

	static void MouseClicked(int button, int state, int x, int y);
	static void MouseMovedPassive(int x,int y);
	static void KeyPressed (unsigned char key, int x, int y);
	static void KeyReleased (unsigned char key, int x, int y);
	static void KeyPressedSpecial(int key, int x, int y);
	static void KeyReleasedSpecial(int key, int x, int y);

	static void Timer(int value);

	static void WindowResize(GLsizei width, GLsizei height);

	~Controller(void);
};
