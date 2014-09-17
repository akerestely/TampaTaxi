#include "Wheel.h"

class Car:public Drawable
{
	Point position;
	double width;
	Wheel **w;
public:
	Car(Point center);
	void Draw();
	~Car();
};

