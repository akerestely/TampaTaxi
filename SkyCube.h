#pragma once
#include"Drawable.h"
#include"Object3d.h"

//!  A class used to draw the sky cube
class SkyCube : public Object3d, public Drawable
{
public:
	SkyCube();
	//! The function used to draw the object on the screen
	void Draw();
	//! Sets the center of the sky cube. Usually needs to be set to the position of the camera.
	/*!
		\param point, a point representing the center of the scky cube
	*/
	void SetPoz(Point point);
};
