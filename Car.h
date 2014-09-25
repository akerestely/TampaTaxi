#pragma once
#include "Wheel.h"
#include "Movable.h"

#define MAX_SPEED 4.0
#define MIN_SPEED -0.2

class Car: public Movable, public Drawable
{
	double wheelBase;
	double speed;
	double steerAngle;
	bool bTurn;
	Wheel **w;
	
	SF3dVector fTraction;
	SF3dVector velocity;

	unsigned int side;
	unsigned int front;
	unsigned int back;
	
	void turn(double steerAngle);
	void computeSteerAngle(int direction);
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

