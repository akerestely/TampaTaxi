#pragma once
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
	static const int MAX_LEVELS = 10;
	int level;
	int objectsCount;
	std::vector<Node*> nodesObj;
	std::vector<Building*> buildingsObj;
	Rectangl bounds;
	QuadTree* nodes[4];
	void split();
	

public:
	QuadTree(int pLevel, Rectangl bounds);
	void Clear();
	void Insert(Node* node);
	void Insert(Building* building);
	void Retrieve(Point position, std::vector<Node*>& returnObjects);
	void Retrieve(Point position, std::vector<Building*>& returnObjects);
	int GetIndex(Point position);
	//int GetLevel(Point Position);
	~QuadTree(void);
};
