#include "Movable.h"
#include "Tools.h"

#include "math.h"

Movable::Movable(Point center,double width, double height)
	:Collidable(center,width,height)
{
	computeViewDir();
}

void Movable::computeViewDir()
{
	viewDir.x=  cos(angle+PI/2);
	viewDir.z= -sin(angle+PI/2);
}

void Movable::IncrementAngle(double deltaAngle)
{
	Collidable::IncrementAngle(deltaAngle);
	computeViewDir();
}

void Movable::SetAngle(double angle)
{
	Collidable::SetAngle(angle);
	computeViewDir();
}
void Movable::SetViewDir(SF3dVector normalizedVector)
{
	viewDir=normalizedVector;
	angle=atan2(normalizedVector.z,-normalizedVector.x)+PI/2;
}
bool Movable::CollidesWith()
{
	Point M;
	for(int j=0; j<4; j++)
	{
		if(j==0)
			M=GetTopRight();
		if(j==1)
			M=GetTopLeft();
		if(j==2)
			M=GetBottomRight();
		if(j==3)
			M=GetBottomLeft();
		for(int i=0; i<(*colliders).size(); i++)
		{
			if((*colliders)[i]!=(Collidable*)this)
			{
				Point A=(*colliders)[i]->GetTopRight();
				Point B=(*colliders)[i]->GetBottomRight();
				Point C=(*colliders)[i]->GetBottomLeft();
				Point D=(*colliders)[i]->GetTopLeft();
				
				if (Tools::PointInsideRectangle(M, A, B, C, D))
					return true;
				
			}
		}
	}
	for(int j=0; j<4*(*colliders).size(); j++)
	{
		if(j%4==0)
			M=(*colliders)[j/4]->GetTopRight();
		if(j%4==1)
			M=(*colliders)[j/4]->GetTopLeft();
		if(j%4==2)
			M=(*colliders)[j/4]->GetBottomRight();
		if(j%4==3)
			M=(*colliders)[j/4]->GetBottomLeft();
		for(int i=0; i<4; i++)
		{
			if((*colliders)[j/4]!=(Collidable*)this)
			{
				Point A=GetTopRight();
				Point B=GetBottomRight();
				Point C=GetBottomLeft();
				Point D=GetTopLeft();
		
				if (Tools::PointInsideRectangle(M, A, B, C, D))
					return true;
			}
		}
	}
	return false;
}

bool Movable::MoveWith(double speed)
{
	double dx,dz;
	dx=-speed*viewDir.x;
	dz=-speed*viewDir.z;

	center.x+=dx;
	center.z+=dz;
	if( CollidesWith() )
	{
		center.x-=dx;
		center.z-=dz;
		return false;
	}

	return true;
}

bool Movable::MoveWith(SF3dVector speedVector)
{
	center.x+=speedVector.x;
	center.z+=speedVector.z;

	if( CollidesWith() )
	{
		center.x-=speedVector.x;
		center.z-=speedVector.z;
		return false;
	}
	return true;
}

