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
	bool isOneWay;
	void getIntersection(Node first, Node second, Point &firstPoint, Point &secondPoint);
	void drawStreetPortion(int index);
public:
	Way(){}
	Way(char* name, std::vector<Node*> nodes, bool isOneWay);
	void ComputeStreet();
	char* GetName();
	std::vector<Node*>& GetNodes();
	void Draw() override;
	~Way(void);
};
