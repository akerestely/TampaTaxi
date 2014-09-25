#pragma once
#include "map"

#include "Drawable.h"
#include "Way.h"

class Minimap: public Drawable, public Object3d
{
	std::map<long, Way*> ways;

	Point currentPosition;
	Point *checkpoint;
public:
	Minimap(std::map<long, Way*> ways, Point center);
	void UpdateCurrentPosition(Point newPosition);
	void UpdateCheckpoint(Point* newCheckPoint);
	void Draw() override;
	~Minimap();
};

