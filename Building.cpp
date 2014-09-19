#include "ctime"
#include "cmath"
#include "Building.h"
#include "Texture.h"
//only for SCALLING define
#include "Node.h"

Building::Building(std::vector<Point> buildingPoints)
	:Object3d(Point())
{
	int mytime = rand()%5;
	Texture tex=Texture::GetInstance();
	myTexture = tex.textures[mytime];
	for(int i=0;i<buildingPoints.size();i++) 
	{
		Point toPush = buildingPoints[i];
		toPush.x = ((toPush.x - 45) * 60 - 38) * SCALLING;
		toPush.y = 0;
		toPush.z = ((toPush.z - 25) * 60 - 34) * SCALLING;
		this->center.x += toPush.x;
		this->center.z += toPush.z;
		this->buildingPoints.push_back(toPush);
	}
	this->center.x /= buildingPoints.size();
	this->center.z /= buildingPoints.size();
}

void Building::Draw() 
{
	int h = 200;
	glBegin(GL_POLYGON);
	for(int i=0;i<buildingPoints.size();i++) 
		glVertex3f( buildingPoints[i].x,h, buildingPoints[i].z);
	glEnd();

	Texture tex=Texture::GetInstance();
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.textures[6]);
	glBegin(GL_QUADS);
	{
		for(int i=0;i<buildingPoints.size();i++) 
		{
			if(i==0) 
			{
				glTexCoord2f(1.0, 1.0);glVertex3f( buildingPoints[buildingPoints.size()-1].x,0, buildingPoints[buildingPoints.size()-1].z);
				glTexCoord2f(1.0, 0.0);glVertex3f( buildingPoints[buildingPoints.size()-1].x,h, buildingPoints[buildingPoints.size()-1].z);
				glTexCoord2f(0.0, 0.0);glVertex3f( buildingPoints[0].x,h, buildingPoints[0].z);
				glTexCoord2f(0.0, 1.0);glVertex3f( buildingPoints[0].x,0, buildingPoints[0].z);
			}
			else 
			{
				glTexCoord2f(1.0, 1.0);glVertex3f( buildingPoints[i-1].x,0, buildingPoints[i-1].z);
				glTexCoord2f(1.0, 0.0);glVertex3f( buildingPoints[i-1].x,h, buildingPoints[i-1].z);
				glTexCoord2f(0.0, 0.0);glVertex3f( buildingPoints[i].x,h, buildingPoints[i].z);
				glTexCoord2f(0.0, 1.0);glVertex3f( buildingPoints[i].x,0, buildingPoints[i].z);
			}
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D); 
}

void Building::Translate(double dx, double dy, double dz)
{
	for(std::vector<Point>::iterator pointIt = buildingPoints.begin(); pointIt != buildingPoints.end(); ++pointIt)
	{
		(*pointIt).x += dx;
		(*pointIt).y += dy;
		(*pointIt).z += dz;

	}
}

Building::~Building(void)
{
}
