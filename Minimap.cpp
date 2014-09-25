#include "Minimap.h"

#include "glut.h"

Minimap::Minimap(std::map<long, Way*> ways, Point center)
:ways(ways), currentPosition(NULL), checkpoint(NULL), Object3d(center)
{
	
}
void Minimap::UpdateCurrentPosition(Point newPosition)
{
	currentPosition = newPosition;
}
void Minimap::UpdateCheckpoint(Point* newCheckPoint)
{
	checkpoint = newCheckPoint;
}
void Minimap::Draw()
{
	glPushMatrix();
	
	glTranslated(center.x, center.y, center.z);
	glScaled(0.01, 1, 0.01);

	glBegin(GL_QUADS);
		glColor3f(1, 0, 0);
		glVertex3d(currentPosition.x - 10, currentPosition.y, currentPosition.z - 10);
		glVertex3d(currentPosition.x - 10, currentPosition.y, currentPosition.z + 10);
		glVertex3d(currentPosition.x + 10, currentPosition.y, currentPosition.z + 10);
		glVertex3d(currentPosition.x + 10, currentPosition.y, currentPosition.z - 10);
	glEnd();

	if (checkpoint != NULL)
	{
		glBegin(GL_QUADS);
			glColor3f(1, 1, 0);
			glVertex3d(checkpoint->x - 10, checkpoint->y, checkpoint->z - 10);
			glVertex3d(checkpoint->x - 10, checkpoint->y, checkpoint->z + 10);
			glVertex3d(checkpoint->x + 10, checkpoint->y, checkpoint->z + 10);
			glVertex3d(checkpoint->x + 10, checkpoint->y, checkpoint->z - 10);
		glEnd();
	}

	for (std::map<long, Way*>::iterator it = ways.begin(); it != ways.end(); ++it)
	{
		(*it).second->Draw();
	}
	glPopMatrix();
}

Minimap::~Minimap()
{
}
