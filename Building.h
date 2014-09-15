#pragma once
#include"Drawable.h"
#include <glut.h>
class Building:public Drawable
{
private:
	double size;
	int type;
	bool mode;
	void model1(double w, double h);
	double angleOfRotation;
	GLuint myTexture;
	double width,length,height;
public:
	Building(Point center,double size, int type,double angleOfRotation);
	void Draw();
	void SwitchMode(Point p,double rotY);
	~Building(void);
};
