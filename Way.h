#pragma once
#include"Node.h"

struct Street
{
	Point corners[4];
};
class Way: public Drawable
{
	char* name;
	std::vector<Node*> nodes;
	std::vector<Street> streetPortions;
	std::vector<Street> leftSidewalkPortions;
	std::vector<Street> rightSidewalkPortions;

	bool isOneWay;
	void getIntersection(Node first, Node second, double diameter, Point &firstPoint, Point &secondPoint);
	void drawStreetPortion(int index);
public:
	Way(){}
	Way(char* name, std::vector<Node*> nodes, bool isOneWay);
	void ComputeStreet();
	char* GetName();
	std::vector<Node*>& GetNodes();
	void Draw() override;
	int GetIndex(Node* node);
	Street* GetPortionStreet(int index);
	Street* GetLeftSidewalk(int index);
	Street* GetRightSidewalk(int index);
	Node* GetNode(int index);
	~Way(void);
};
