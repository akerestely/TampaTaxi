#pragma once
#include "Drawable.h"
#include"Texture.h"
class Hud :public Drawable
{
	GLuint hudTex;
public:
	Hud();
	Hud(Point center);
	void Draw();
	~Hud(void);
};
