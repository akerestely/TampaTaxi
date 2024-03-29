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
Point* Minimap::GetChekcpoint()
{
	return checkpoint;
}
void Minimap::Draw()
{
	glPushMatrix();
	glLoadIdentity();
	
	glTranslated(0, -20, -120);
	glRotated(90,1,0,0);
	glRotated(45,0,1,0);
	glScaled(0.01, 1, 0.01);
	glTranslated(-center.x, 0, -center.z);

	glBegin(GL_QUADS);
		glColor3f(1, 0, 0);
		glVertex3d(currentPosition.x - 30, currentPosition.y , currentPosition.z - 30);
		glVertex3d(currentPosition.x - 30, currentPosition.y , currentPosition.z + 30);
		glVertex3d(currentPosition.x + 30, currentPosition.y , currentPosition.z + 30);
		glVertex3d(currentPosition.x + 30, currentPosition.y , currentPosition.z - 30);
	glEnd();

	if (checkpoint != NULL)
	{
		glBegin(GL_QUADS);
			glColor3f(1, 1, 0);
			glVertex3d(checkpoint->x - 30, checkpoint->y, checkpoint->z - 30);
			glVertex3d(checkpoint->x - 30, checkpoint->y, checkpoint->z + 30);
			glVertex3d(checkpoint->x + 30, checkpoint->y, checkpoint->z + 30);
			glVertex3d(checkpoint->x + 30, checkpoint->y, checkpoint->z - 30);
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
