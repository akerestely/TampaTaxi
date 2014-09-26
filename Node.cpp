#include "Node.h"
#include "Texture.h"

#include "glut.h"
#include "cmath"

Node::Node(Point center, long id)
	:Object3d(center),id(id)
{
	this->center.x = ((center.x - 45) * 60 - 38) * SCALLING;
	this->center.y = center.y;
	this->center.z = ((center.z - 25) * 60 - 34) * SCALLING;
}
void Node::Draw(bool isSidewalk)
{
	double diameter, dy;
	Texture tex = Texture::GetInstance();
	glEnable(GL_TEXTURE_2D);
	if(isSidewalk)
	{
		diameter = SIDEWALK_DIAMETER;
		dy = 0.03;
		glBindTexture(GL_TEXTURE_2D, tex.sidewayTex);
	}
	else
	{
		diameter = NODE_DIAMETER;
		dy = 0.05;
		glBindTexture(GL_TEXTURE_2D, tex.roadTex);
	}
	
	glBegin(GL_TRIANGLE_FAN);
	for(int theta = 0; theta <= 360; theta+=18)
	{
		glTexCoord2d((cos(theta * PIdiv180) + 1) / 2 * 10,(sin(theta * PIdiv180) + 1) / 2 * 10);
		glVertex3d(center.x + diameter / 2 * cos(theta * PIdiv180), center.y + dy, center.z + diameter / 2 * sin(theta * PIdiv180));
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
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
long Node::GetId()
{
	return id;
}
Node::~Node(void)
{
}
