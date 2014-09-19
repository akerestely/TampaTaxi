#pragma once
#include <vector>
#include "Object3d.h"
#include "Drawable.h"

class Building: public Object3d, public Drawable
{
private:
	double size;
	int type;
	bool mode;
	double buildingHeight;
	double angleOfRotation;
	unsigned int myTexture;
	double width,length,height;
public:
	std::vector<Point> buildingPoints;
	Building(std::vector<Point> buildingPoints);
	void Draw();
	void Translate(double dx, double dy, double dz);
	~Building(void);
};
