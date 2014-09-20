#include "Wheel.h"
#include "Movable.h"

class Car: public Movable, public Drawable
{
	Point position;
	double width;
	Wheel **w;
	unsigned int side;
public:
	Car(Point center);
	void Draw();
	~Car();
};

