#pragma once
#include "Drawable.h"

class Player : public Drawable
{
public:
	Player(Point center);
	void Draw();
	~Player(void);
};
