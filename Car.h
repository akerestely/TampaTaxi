#pragma once
#include "Wheel.h"
#include "Movable.h"

#define MAX_SPEED 4.0
#define MIN_SPEED -0.2

class Car: public Movable, public Drawable
{
	double wheelBase;
	double carHeading;
	double speed;
	Wheel **w;
	unsigned int side;

	SF3dVector fTraction;
	SF3dVector velocity;

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

