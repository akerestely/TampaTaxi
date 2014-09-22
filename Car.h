#pragma once
#include "Wheel.h"
#include "Movable.h"

#define MAX_SPEED 1.0

class Car: public Movable, public Drawable
{
	double speed;
	Wheel **w;
	unsigned int side;
public:
	Car(Point center);
	double GetSpeed();
	void Accelerate(double deltaSpeed);
	void Update();
	void Draw();
	~Car();
};

