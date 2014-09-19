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
	std::map<long, Node> nodes;
	std::vector<Building> buildings;
	
	std::set<long> waysToDraw;
	std::vector<Building*>buildingsToDraw;
	
	void loadNodes(char* nodesFile);
	void loadBuildings(char* buildingsFile);
public:
	Map(char* nodesFile, char* buildingsFile);
	void AddBuildings(std::vector<Building>& building);
	void Draw() override;
	void Update(Point camPosition);
	~Map(void);
};
