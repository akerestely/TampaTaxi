#include "Map.h"
#include "Tools.h"

#include "cmath"
#include "glut.h"

Map::Map(char *nodesFile, char *buildingsFile)
:Object3d(Point()), topLeftMapPoint(Point(+1000000, 0, +1000000)), bottomRightPoint(Point(-1000000, 0, -100000))
{
	loadNodes(nodesFile);
	loadBuildings(buildingsFile);
	initQuadTree();
}
void Map::loadNodes(char *nodesFile)
{
	Tools::ReadNodesFromXML(nodesFile, nodes, ways);
	center = nodes[START_NODE]->GetCenter();
	for(std::map<long, Node*>::iterator nodesIt = nodes.begin(); nodesIt != nodes.end(); ++nodesIt)
	{
		((*nodesIt).second)->Translate(-center.x, 0, -center.z);
		Point p = ((*nodesIt).second)->GetCenter();
		if (p.x < topLeftMapPoint.x)
			topLeftMapPoint.x = p.x;
		if (p.x > bottomRightPoint.x)
			bottomRightPoint.x = p.x;
		if (p.z < topLeftMapPoint.z)
			topLeftMapPoint.z = p.z;
		if (p.z > bottomRightPoint.z)
			bottomRightPoint.z = p.z;
	}
	
	for(std::map<long, Way*>::iterator waysIt = this->ways.begin(); waysIt != this->ways.end(); ++waysIt)
	{
		(*waysIt).second->ComputeStreet();
	}	
	waysToDraw.clear();
}
void Map::loadBuildings(char *buildingsFile)
{
	Tools::ReadBuildingsFromXML(buildingsFile, buildings);
	for(std::vector<Building*>::iterator buildingIt = buildings.begin(); buildingIt != buildings.end(); ++buildingIt)
	{
		(*buildingIt)->Translate(-center.x, 0, -center.z);
		Point p = (*buildingIt)->GetCenter();
		if (p.x < topLeftMapPoint.x)
			topLeftMapPoint.x = p.x;
		if (p.x > bottomRightPoint.x)
			bottomRightPoint.x = p.x;
		if (p.z < topLeftMapPoint.z)
			topLeftMapPoint.z = p.z;
		if (p.z > bottomRightPoint.z)
			bottomRightPoint.z = p.z;
	}
	buildingsToDraw.clear();
}
void Map::initQuadTree()
{
	drawableQuadTree = new QuadTree(0, Rectangl(topLeftMapPoint.x - 1, topLeftMapPoint.z - 1, bottomRightPoint.x - topLeftMapPoint.x + 1, bottomRightPoint.z - topLeftMapPoint.z + 1));
	for (std::map<long, Node*>::iterator nodesIt = nodes.begin(); nodesIt != nodes.end(); ++nodesIt)
	{
		drawableQuadTree->Insert(((*nodesIt).second));
	}
	for (std::vector<Building*>::iterator buildingIt = buildings.begin(); buildingIt != buildings.end(); ++buildingIt)
	{
		drawableQuadTree->Insert(*buildingIt);
	}
}
void Map::Draw()
{
	Point first, second;

	for(std::set<long>::iterator waysIt = waysToDraw.begin(); waysIt != waysToDraw.end(); ++waysIt)
		ways[*waysIt]->Draw();
	for(std::set<Building*>::iterator buildingIt = buildingsToDraw.begin(); buildingIt != buildingsToDraw.end(); ++buildingIt)
	{
		(*buildingIt)->Draw();
	}

}
void Map::Update(Point camPosition, double camAngle)
{
	std::set<int> visitedQuadrants;
	std::set<Node*> nodes;

	waysToDraw.clear();
	buildingsToDraw.clear();
	
	drawableQuadTree->Retrieve(buildingsToDraw, camPosition);
	drawableQuadTree->Retrieve(nodes, camPosition);
	
	int camPositionIndex = drawableQuadTree->GetNodeIndex(camPosition);
	visitedQuadrants.insert(camPositionIndex);
	double angle = camAngle - 90;
	for (double radius = 50; radius < 500; radius += 150)
	{
		for (int i = 0; i < 5; i++, angle += 45)
		{
			Point p = Point(camPosition.x + radius * cos(angle * PIdiv180), camPosition.y, camPosition.z + radius * sin(angle * PIdiv180));
			int nextPositionIndex = drawableQuadTree->GetNodeIndex(p);
			if (!visitedQuadrants.count(nextPositionIndex))
			{
				
				drawableQuadTree->Retrieve(buildingsToDraw, p);
				if (radius < 201)
					drawableQuadTree->Retrieve(nodes, p);
				visitedQuadrants.insert(nextPositionIndex);
			}
		}
	}

	for(std::set<Node*>::iterator nodesIt = nodes.begin(); nodesIt != nodes.end(); ++nodesIt)
	{
		waysToDraw.insert((*nodesIt)->GetWays().begin(), (*nodesIt)->GetWays().end());
	}
}
Node* Map::GetNode(long id)
{
	return nodes[id];
}
Way* Map::GetWay(long id)
{
	return ways[id];
}
std::set<long>* Map::GetWaysToDraw()
{
	return &waysToDraw;
}

Map::~Map(void)
{
}
