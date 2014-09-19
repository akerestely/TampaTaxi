#include "Node.h"
#include "glut.h"
#include "cmath"

Node::Node(Point center)
	:Object3d(center)
{
	this->center.x = ((center.x - 45) * 60 - 38) * SCALLING;
	this->center.y = center.y;
	this->center.z = ((center.z - 25) * 60 - 34) * SCALLING;
	//this->center.x = (center.x - 45.6) * 10 * SCALLING;
	//this->center.y = center.y;
	//this->center.z = (center.z - 25.5) * 10 * SCALLING;
}
void Node::Draw()
{
	glBegin(GL_TRIANGLE_FAN);
	
	//glTexCoord2d(0.5, 0.5);
	glVertex3d(center.x, center.y, center.z);
	for(int theta = 0; theta <= 360; theta++)
	{
	//	glTexCoord2d((cos(theta * PI / 180) + 1) / 2, (sin(theta * PI / 180) + 1) / 2);
		glVertex3d(center.x + NODE_DIAMETER / 2 * cos(theta * PI / 180), center.y, center.z + NODE_DIAMETER / 2 * sin(theta * PI / 180));
	}
	glEnd();
	
}
void Node::AddWay(long id)
{
	this->ways.push_back(id);
}
std::vector<long>& Node::GetWays()
{
	return this->ways;
}
void Node::Translate(double dx, double dy, double dz)
{
	center.x += dx;
	center.y += dy;
	center.z += dz;
}
Node::~Node(void)
{
}
