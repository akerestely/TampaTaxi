#pragma once
#include "Point.h"


//! An abstanct class that can be drawn on screen
class Drawable
{
protected:
	//! Center of the object
	Point center;
public:
	Drawable(Point center);
	Drawable();
	//! The function used to draw the object on the screen
	virtual void Draw() = 0;
};
