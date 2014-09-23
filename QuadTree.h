#pragma once
#include "set"

#include "Node.h"
#include "Building.h"
#include "Tools.h"


class QuadTree
{
    static const int MAX_OBJECTS = 50;
	static const int MAX_LEVELS = 5;
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
	void Retrieve(std::set<Node*>& returnObjects, Point position);
	void Retrieve(std::set<Building*>& returnObjects, Point position);
	int GetIndex(Point position);
	int GetNodeIndex(Point position);
	~QuadTree(void);
};
