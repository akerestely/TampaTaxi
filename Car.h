#pragma once
#include "Wheel.h"
#include "Movable.h"

#define MAX_SPEED 1.0
#define MIN_SPEED -0.2

class Car: public Movable, public Drawable
{
	double speed;
	Wheel **w;
	unsigned int side;
public:
	Car(Point center);
	double GetSpeed();
	void Accelerate();
	void Break();
	void Reverse();
	void TurnLeft();
	void TurnRight();
	void Update();
	void Draw();
	~Car();
};

