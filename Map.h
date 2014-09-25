#pragma once
#include "set"

#include "Minimap.h"
#include "QuadTree.h"

#define START_NODE 1798

class Map : public Object3d, public Drawable
{
private:
	QuadTree* drawableQuadTree;
	Minimap *miniMap;

	std::map<long,Way*> ways;
	std::map<long, Node*> nodes;
	std::vector<Building*> buildings;
	
	std::set<long> waysToDraw;
	std::set<Building*>buildingsToDraw;

	Point topLeftMapPoint;
	Point bottomRightPoint;
	Point checkPoint;
	Point currentPosition;

	char currentWayName[40];
	
	void loadNodes(char* nodesFile);
	void loadBuildings(char* buildingsFile);
	void initQuadTree();
	void initMinimap();
public:
	Map(char* nodesFile, char* buildingsFile);
	void AddBuildings(std::vector<Building>& building);
	void Draw() override;
	void Update(Point camPosition, double camAngle);
	void SetCheckpoint(Point newCheckpoint);
	Node* GetNode(long id);
	Way* GetWay(long id);
	std::set<long>* GetWaysToDraw();
	Minimap* GetMinimap();
	Point GenerateCheckpoint(double distance);
	char* GetCurrentWayName();
	void Map::StreetCollision(Node *node, Point M, int& insidePoints);
	~Map(void);
};
