#pragma once
#include "set"

#include "Node.h"
#include "Building.h"

struct Rectangl{
	int x, y;
	int height, width;
	Rectangl(int x = 0,int y = 0,int height = 0,int width = 0)
		:x(x),y(y),height(height),width(width)
	{
	}
};

class QuadTree
{
    static const int MAX_OBJECTS = 500;
	static const int MAX_LEVELS = 4;
	int level;
	int nodeIndex;
	int objectsCount;
	std::vector<Node*> nodesObj;
	std::vector<Building*> buildingsObj;
	Rectangl bounds;
	QuadTree* nodes[4];
	void split();
	

public:
	QuadTree(int pLevel, Rectangl bounds, int nodeIndex = 0);
	void Clear();
	void Insert(Node* node);
	void Insert(Building* building);
	void Retrieve(std::set<Node*>& returnObjects, Point position, double radius = 0);
	void Retrieve(std::set<Building*>& returnObjects, Point position, double radius = 0);
	int GetIndex(Point position);
	int GetNodeIndex(Point position);
	~QuadTree(void);
};
