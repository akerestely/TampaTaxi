#include "Movable.h"
#include "Tools.h"

#include "math.h"

Movable::Movable(Point center,double width, double height)
	:Collidable(center,width,height)
{
	canMove=true;
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
	dx=-speed*cos(angle+PI/2);
	dz=-speed* -sin(angle+PI/2);

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

