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
	Point leftStreetCorner, rightStreetCorner;
	Point leftSidewalkCorner, rightSidewalkCorner;
	Street newStreet, leftSidewalk, rightSidewalk;

	for (int i = 0 ; i < nodes.size() - 1; i++)
	{
		getIntersection(*nodes[i], *nodes[i+1], NODE_DIAMETER, leftStreetCorner, rightStreetCorner);
		getIntersection(*nodes[i], *nodes[i+1], SIDEWALK_DIAMETER, leftSidewalkCorner, rightSidewalkCorner);
		
		newStreet.corners[0] = leftStreetCorner;
		newStreet.corners[1] = rightStreetCorner;
		leftSidewalk.corners[0] = leftSidewalkCorner;
		leftSidewalk.corners[1] = leftStreetCorner;
		rightSidewalk.corners[0] = rightStreetCorner;
		rightSidewalk.corners[1] = rightSidewalkCorner;

		getIntersection(*nodes[i+1], *nodes[i], NODE_DIAMETER, leftStreetCorner, rightStreetCorner);
		getIntersection(*nodes[i+1], *nodes[i], SIDEWALK_DIAMETER, leftSidewalkCorner, rightSidewalkCorner);
		
		newStreet.corners[2] = rightStreetCorner;
		newStreet.corners[3] = leftStreetCorner;
		leftSidewalk.corners[2] = leftStreetCorner;
		leftSidewalk.corners[3] = leftSidewalkCorner;
		rightSidewalk.corners[2] = rightSidewalkCorner;
		rightSidewalk.corners[3] = rightStreetCorner;
		
		streetPortions.push_back(newStreet);
		leftSidewalkPortions.push_back(leftSidewalk);
		rightSidewalkPortions.push_back(rightSidewalk);
	}
}
void Way::getIntersection(Node first, Node second, double diameter, Point &firstPoint, Point &secondPoint)
{
	Point firstCenter = first.GetCenter();
	Point secondCenter = second.GetCenter();
	double radius = diameter / 2;
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
	glColor3f(1, 0, 0);
	Street portion = leftSidewalkPortions[index];
	glBegin(GL_QUADS);
	glVertex3d(portion.corners[0].x, portion.corners[0].y - 0.05, portion.corners[0].z);
	glVertex3d(portion.corners[1].x, portion.corners[1].y - 0.05, portion.corners[1].z);
	glVertex3d(portion.corners[2].x, portion.corners[2].y - 0.05, portion.corners[2].z);
	glVertex3d(portion.corners[3].x, portion.corners[3].y - 0.05, portion.corners[3].z);
	glEnd();
	
	portion = rightSidewalkPortions[index];
	glBegin(GL_QUADS);
	glVertex3d(portion.corners[0].x, portion.corners[0].y - 0.05, portion.corners[0].z);
	glVertex3d(portion.corners[1].x, portion.corners[1].y - 0.05, portion.corners[1].z);
	glVertex3d(portion.corners[2].x, portion.corners[2].y - 0.05, portion.corners[2].z);
	glVertex3d(portion.corners[3].x, portion.corners[3].y - 0.05, portion.corners[3].z);
	glEnd();

	glColor3f(1, 1, 0);
	portion = streetPortions[index];
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
		nodes[i]->Draw(true);
		nodes[i]->Draw(false);
		drawStreetPortion(i);
	}
	nodes[count-1]->Draw(true);
	nodes[count-1]->Draw(false);
}
int Way::GetIndex(Node* node)
{
	for(int i = 0; i < nodes.size(); i++)
		if (nodes[i] == node)
			return i;
	return -1;
}
Street* Way::GetPortionStreet(int index)
{
	if (index < 0 || index >= streetPortions.size())
		return NULL;
	return &streetPortions[index];
}
Node* Way::GetNode(int index)
{
	if (index < 0 || index >= nodes.size())
		return NULL;
	return nodes[index];
}
Way::~Way(void)
{

}
