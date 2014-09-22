#pragma once
#include "Drawable.h"
#include "Collidable.h"
#include "Car.h"

class Player : public Drawable
{
	Car *car;
public:
	int LastVisitedNodeIndex;
	Player(Car* car);
	void Draw();
	Point GetPosition();
	Collidable* GetPlayerState();
	~Player(void);
};


