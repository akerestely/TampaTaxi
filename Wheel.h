#include "Drawable.h"
#include "Object3d.h"

class Wheel : public Object3d, public Drawable
{
	Point position;
	double radius,width;
	unsigned int side;
	unsigned int base;
	double angleRotation;
public:
	Wheel(Point center,double r,double w);
	void IncrementRotationAngle(double deltaAngle);
	void Draw();
	~Wheel();
};

