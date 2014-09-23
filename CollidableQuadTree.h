#pragma once
#include "vector"
#include "set"

#include "Collidable.h"
#include "Tools.h"

class CollidableQuadTree
{
	static const int MAX_OBJECTS = 500;
	static const int MAX_LEVELS = 4;
	int level;
	int nodeIndex;
	std::vector<Collidable*> objects;
	Rectangl bounds;
	CollidableQuadTree* nodes[4];
	void split();
public:
	CollidableQuadTree(int pLevel, Rectangl bounds, int nodeIndex = 0);
	void Clear();
	void Insert(Collidable* collidable);
	void Retrieve(std::set<Collidable*>& returnObjects, Point position);
	int GetIndex(Point position);
	int GetNodeIndex(Point position);
	~CollidableQuadTree(void);
};
