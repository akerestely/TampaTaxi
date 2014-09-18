#include "Wheel.h"

class Car:public Drawable
{
	Point position;
	double width;
	Wheel **w;
	double wheelRadius;
public:
	Car(Point center);
	void Draw();
	~Car();
};

