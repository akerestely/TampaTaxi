#include "Map.h"
#include "Tools.h"

#include "glut.h"

Map::Map(char *nodesFile, char *buildingsFile)
	:Object3d(Point())
{
	loadNodes(nodesFile);
	loadBuildings(buildingsFile);
}
void Map::loadNodes(char *nodesFile)
{
	Tools::ReadNodesFromXML(nodesFile, nodes, ways);
	center = nodes[756].GetCenter();
	int minX = 1000000, maxX = -1000000, minZ = 1000000, maxZ = -1000000;
	for(std::map<long, Node>::iterator nodesIt = nodes.begin(); nodesIt != nodes.end(); ++nodesIt)
	{

		Node *toInsert = &((*nodesIt).second);
		toInsert->Translate(-center.x, 0, -center.z);
		Point p = toInsert->GetCenter();
		
		if(p.x < minX)
			minX = p.x;
		if (p.x > maxX)
			maxX = p.x;
		if(p.z < minZ)
			minZ = p.z;
		if (p.z > maxZ)
			maxZ = p.z;
	}
	drawableQuadTree = new QuadTree(0, Rectangl(minX - 1, minZ - 1, maxX - minX + 1, maxZ - minZ + 1));
	for(std::map<long, Node>::iterator nodesIt = nodes.begin(); nodesIt != nodes.end(); ++nodesIt)
	{
		drawableQuadTree->Insert(&((*nodesIt).second));
	}
	for(std::map<long, Way>::iterator waysIt = this->ways.begin(); waysIt != this->ways.end(); ++waysIt)
	{
		(*waysIt).second.ComputeStreet();
	}	
	waysToDraw.clear();
}
void Map::loadBuildings(char *buildingsFile)
{
	Tools::ReadBuildingsFromXML(buildingsFile, buildings);
	for(std::vector<Building>::iterator buildingIt = buildings.begin(); buildingIt != buildings.end(); ++buildingIt)
	{
		Building *building = &*buildingIt;
		building->Translate(-center.x, 0, -center.z);
		drawableQuadTree->Insert(building);
	}
	buildingsToDraw.clear();
}

void Map::Draw()
{
	
	Point first, second;
	/*glColor3f(1, 0, 0);
	for(std::map<long, Way>::iterator waysIt = ways.begin(); waysIt != ways.end(); ++waysIt)
		if(!waysToDraw.count(waysIt->first))
			(*waysIt).second.Draw();*/


	glColor3f(0.9, 1, 0);
	for(std::set<long>::iterator waysIt = waysToDraw.begin(); waysIt != waysToDraw.end(); ++waysIt)
		ways[*waysIt].Draw();
	for(std::vector<Building*>::iterator buildingIt = buildingsToDraw.begin(); buildingIt != buildingsToDraw.end(); ++buildingIt)
	{
		(*buildingIt)->Draw();
	}

}
void Map::Update(Point camPosition)
{
	
	waysToDraw.clear();
	buildingsToDraw.clear();
	drawableQuadTree->Retrieve(camPosition, buildingsToDraw);
	std::vector<Node*> nodes;
	drawableQuadTree->Retrieve(camPosition, nodes);	
	for(std::vector<Node*>::iterator nodesIt = nodes.begin(); nodesIt != nodes.end(); ++nodesIt)
	{
		waysToDraw.insert((*nodesIt)->GetWays().begin(), (*nodesIt)->GetWays().end());
	}
}
Map::~Map(void)
{
}
