#pragma once
#include "Drawable.h"
#include "Object3d.h"

class Player : public Object3d, public Drawable
{
public:
	Player(Point center);
	void Draw();
	~Player(void);
};
