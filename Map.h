#pragma once
#include "map"
#include "set"
#include "QuadTree.h"
#include "Way.h"

#define START_NODE 1798

class Map : public Object3d, public Drawable
{
private:
	QuadTree* drawableQuadTree;
	std::map<long,Way*> ways;
	std::map<long, Node*> nodes;
	std::vector<Building*> buildings;
	
	std::set<long> waysToDraw;
	std::set<Building*>buildingsToDraw;

	Point topLeftMapPoint;
	Point bottomRightPoint;
	
	void loadNodes(char* nodesFile);
	void loadBuildings(char* buildingsFile);
	void initQuadTree();
public:
	Map(char* nodesFile, char* buildingsFile);
	void AddBuildings(std::vector<Building>& building);
	void Draw() override;
	void Update(Point camPosition, double camAngle);
	Node* GetNode(long id);
	Way* GetWay(long id);
	std::set<long>* GetWaysToDraw();
	~Map(void);
};
