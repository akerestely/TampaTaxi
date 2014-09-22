#pragma once
#include <vector>
#include "Point.h"
#include "Texture.h"
class MainMenu
{
public:
	MainMenu(void);
	~MainMenu(void);
	GLuint newGameButton;
	std::vector<Point> menuPoints;
	void Draw() ;
};
