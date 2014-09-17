#pragma once
#include "Object3d.h"

//! An abstanct class that can be drawn on screen
class Drawable : public Object3d
{
public:
	Drawable(Point center);
	//! The function used to draw the object on the screen
	virtual void Draw() = 0;
};
