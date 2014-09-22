#pragma once
//Standard
#include "vector"

//User defined
#include"Object3d.h"
#include"Drawable.h"

#define NODE_DIAMETER 8. 
#define SIDEWALK_DIAMETER 14.
#define SCALLING 10000

class Node: public Object3d
{
	long id;
	std::vector<long> ways;
public:
	Node(Point center, long id);
	void AddWay(long id);
	std::vector<long>& GetWays();
	void Draw(bool isSidewalk);
	void Translate(double dx, double dy, double dz);
	long GetId();
	~Node(void);
};
