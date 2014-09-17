#include "Node.h"
#include "glut.h"
#include "cmath"
Node::Node(int id, Point center)
:id(id),Drawable(Point(-(center.x - 36) * SCALLING,
						center.y,
						(center.z - 39) * SCALLING))
{
	/*this->center.x = -(center.x - 36) * SCALLING;
	this->center.y = center.y;
	this->center.z = (center.z - 39) * SCALLING;*/
}

Node::Node()
:Drawable(Point())
{
	id=-1;
}
void Node::Draw()
{
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2d(0.5, 0.5);
	glVertex3d(center.x, center.y, center.z);
	for(int theta = 0; theta <= 360; theta++)
	{
		glTexCoord2d((cos(theta * PI / 180) + 1) / 2, (sin(theta * PI / 180) + 1) / 2);
		glVertex3d(center.x + BALL_RADIUS / 2 * cos(theta * PI / 180), center.y, center.z + BALL_RADIUS / 2 * sin(theta * PI / 180));
	}
	glEnd();
	glColor3f(1, 1, 1);
}

Point Node::getCenter()
{
	return center;
}

std::vector<int>& Node::getDestinations()
{
	return destinations;
}

void Node::Translate(double dx, double dy, double dz)
{
	this->center.x += dx;
	this->center.y += dy;
	this->center.z += dz;
}
void Node::addStreet(Street street)
{
	streets.push_back(street);
}
Street Node::GetStreet(int index)
{
	if (streets.size() > index)
		return streets[index];
	return Street();
}