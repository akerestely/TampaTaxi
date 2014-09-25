#pragma once
#include<vector>
#include<map>
#include "Point.h"
#include "Node.h"
#include"Way.h"
#include "Building.h"

/*Enum used to notate ball position when rolling on the street
*@param Inside between street markers
*@param Outside outside street markers
**/
enum BallStreetPosition{
	Inside,
	Outside,
};
class Tools
{
	
public:
	/*
	*Static method which read and store all the coordonates of intersection nodes 
	*of the map(by intersection we understand two or more roads which intersect)
	*and all the connections(arcs) between them from an xml file.
	*@param fileName name of the file which contains nodes and arcs
	*@param nodes a map where one should store the nodes.
	*Returns 1 if the read operation succeded, and 0 otherwise.
	**/
	static int ReadNodesFromXML(char *fileName, std::map<long,Node*> &nodes,std::map<long,Way*> &ways);
	/*
	*Static method which read and store all buildings of the map 
	*from an xml file.(coordonates,size,type etc)For more info go to Building Class.
	*@param fileName name of the file which contains buildings data
	*@param buildings a vector where one should store buildings data
	**/
	static int ReadBuildingsFromXML(char* fileName,std::vector<Building*> &buildings);
	static int Sign(double x);

	static bool PointInsideRectangle(Point point, Point rTopRight, Point rBottomRight, Point rBottomLeft, Point rTopLeft);
	static bool PointInsideCircle(Point point, Point cCenter, double cRadius);

	static long LongRand();
};

struct Rectangl{
	int x, y;
	int height, width;
	Rectangl(int x = 0,int y = 0,int height = 0,int width = 0)
		:x(x),y(y),height(height),width(width)
	{
	}
};
