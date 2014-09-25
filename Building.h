#pragma once
#include <vector>
#include "Object3d.h"
#include "Drawable.h"

class Building: public Object3d, public Drawable
{
private:
	double size;
	double height;
	unsigned int texture;
	std::vector<Point> buildingPoints;
public:
	Building(std::vector<Point> buildingPoints, int constRand);
	void Draw();
	void Translate(double dx, double dy, double dz);
	~Building(void);
};
