#include "Way.h"
#include "glut.h"
#include "cmath"


Way::Way(char* name,std::vector<Node*> nodes,bool isOneWay)
	:nodes(nodes),isOneWay(isOneWay)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Way::ComputeStreet()
{
	Point first, second;
	Street newStreet;
	for (int i = 0 ; i < nodes.size() - 1; i++)
	{
		getIntersection(*nodes[i], *nodes[i+1], first, second);
		newStreet.corners[0] = first;
		newStreet.corners[1] = second;
		getIntersection(*nodes[i+1], *nodes[i], first, second);
		newStreet.corners[2] = second;
		newStreet.corners[3] = first;
		streetPortions.push_back(newStreet);
	}
}
void Way::getIntersection(Node first, Node second, Point &firstPoint, Point &secondPoint)
{
	Point firstCenter = first.GetCenter();
	Point secondCenter = second.GetCenter();
	double radius = NODE_DIAMETER / 2;
	double m;
	if (secondCenter.z == firstCenter.z)
		m = 0;
	else
		m = (firstCenter.x - secondCenter.x) / (secondCenter.z - firstCenter.z);
	double alpha = -2 * firstCenter.x;
	double beta = firstCenter.x * firstCenter.x - radius * radius / (1 + m * m);
	double delta = alpha * alpha - 4 * beta;
	if (delta <= 0)
	{
		firstPoint = firstCenter;
		secondPoint = firstCenter;
		return;
	}
	firstPoint.x = (-alpha + sqrt(delta)) / 2;
	secondPoint.x = (-alpha - sqrt(delta)) / 2;
	firstPoint.z = firstCenter.z + m * (firstPoint.x - firstCenter.x);
	secondPoint.z = firstCenter.z + m * (secondPoint.x - firstCenter.x);
	firstPoint.y = firstCenter.y;
	secondPoint.y = firstCenter.y;
}

char* Way::GetName()
{
	return name;
}

std::vector<Node*>& Way::GetNodes()
{
	return nodes;
}
void Way::drawStreetPortion(int index)
{
	Street portion = streetPortions[index];
	glBegin(GL_QUADS);
	glVertex3d(portion.corners[0].x, portion.corners[0].y, portion.corners[0].z);
	glVertex3d(portion.corners[1].x, portion.corners[1].y, portion.corners[1].z);
	glVertex3d(portion.corners[2].x, portion.corners[2].y, portion.corners[2].z);
	glVertex3d(portion.corners[3].x, portion.corners[3].y, portion.corners[3].z);
	glEnd();
}
void Way::Draw()
{
	int count = nodes.size();
	for (int i = 0 ; i < count - 1; i++)
	{
		nodes[i]->Draw();
		drawStreetPortion(i);
	}
	nodes[count-1]->Draw();
	
}

Way::~Way(void)
{

}
