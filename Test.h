#pragma once
#include "Movable.h"
#include "Drawable.h"

class Test : public Movable, public Drawable
{
public:
	Test(Point center, double width,double height);
	~Test(void);
	void Draw() ;
};
