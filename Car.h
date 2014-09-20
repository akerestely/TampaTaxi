#include "Wheel.h"

class Car:public Drawable
{
	Point position;
	double width;
	Wheel **w;
	GLuint side;
public:
	Car(Point center);
	void Draw();
	~Car();
};

