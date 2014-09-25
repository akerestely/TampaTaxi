#include "ctime"
#include "cmath"
#include "Building.h"
#include "Texture.h"
//only for SCALLING define
#include "Node.h"

Building::Building(std::vector<Point> buildingPoints, int constRand)
	:Object3d(Point())
{
	Texture tex=Texture::GetInstance();
	texture = tex.textures[constRand%5];
	height = 20 + 3*constRand%3;

	int n=buildingPoints.size();
	for(std::vector<Point>::iterator it=buildingPoints.begin();it!=buildingPoints.end();++it) 
	{
		Point toPush = *it;
		toPush.x = ((toPush.x - 45) * 60 - 38) * SCALLING ;
		toPush.y = 0;
		toPush.z = ((toPush.z - 25) * 60 - 34) * SCALLING;
		this->center.x += toPush.x / n;
		this->center.z += toPush.z / n;
		this->buildingPoints.push_back(toPush);
	}
}

void Building::Draw() 
{
	glBegin(GL_POLYGON);
	for(std::vector<Point>::iterator it=buildingPoints.begin();it!=buildingPoints.end();++it) 
		glVertex3f( (*it).x, height, (*it).z);
	glEnd();
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	for(std::vector<Point>::iterator it=buildingPoints.begin();it!=buildingPoints.end();++it) 
	{
		if(it==buildingPoints.begin()) 
		{
			glTexCoord2f(1.0, 1.0); glVertex3f( buildingPoints.back().x, 0,      buildingPoints.back().z );
			glTexCoord2f(1.0, 0.0); glVertex3f( buildingPoints.back().x, height, buildingPoints.back().z );
			glTexCoord2f(0.0, 0.0); glVertex3f( buildingPoints.front().x, height, buildingPoints.front().z );
			glTexCoord2f(0.0, 1.0); glVertex3f( buildingPoints.front().x, 0,      buildingPoints.front().z );
		}
		else 
		{
			glTexCoord2f(1.0, 1.0); glVertex3f( (it-1)->x, 0, (it-1)->z);
			glTexCoord2f(1.0, 0.0); glVertex3f( (it-1)->x, height, (it-1)->z);
			glTexCoord2f(0.0, 0.0); glVertex3f( it->x, height, it->z);
			glTexCoord2f(0.0, 1.0); glVertex3f( it->x, 0, it->z);
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
	center.x += dx;
	center.y += dy;
	center.z += dz;
}

Building::~Building(void)
{
}
