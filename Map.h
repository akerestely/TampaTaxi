#pragma once
#include "map"
#include "set"
#include "QuadTree.h"
#include "Way.h"

class Map : public Object3d, public Drawable
{
private:
	QuadTree* drawableQuadTree;
	std::map<long,Way> ways;
	std::set<long> waysToDraw;
	std::vector<Building*>buildingsToDraw;
public:
	Map(std::map<long,Node>& nodes,std::map<long,Way> ways);
	void AddBuildings(std::vector<Building>& building);
	void Draw() override;
	void Update(Point camPosition);
	~Map(void);
};
