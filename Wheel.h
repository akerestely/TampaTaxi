#include "Drawable.h"
#include <glut.h>
class Wheel : public Drawable
{
	Point position;
	double radius,width;
	GLuint side;
	GLuint base;
	double angle;
public:
	Wheel(Point center,double r,double w);
	void Draw();
	~Wheel();
};

