#include "WorldGenerator.h"
#include<math.h>
WorldGenerator::WorldGenerator(Map* cityMap)
{
	this->cityMap=cityMap;
}

void WorldGenerator::Initialize()
{
	for(int i=0;i<150;i++)
	{
		invisiblePoolHuman.push_back(new Human(Point(0.0,0.0,0.0)));
	}
	srand(time(NULL));
}

void WorldGenerator::Update()
{

	
	for(int i=0;i<invisiblePoolHuman.size();i++)
	{	
	int setSize=cityMap->GetWaysToDraw()->size();
	int wayRand,nodeRand;
	int waySize;
		wayRand=rand()%setSize;
		std::set<long>::iterator it=cityMap->GetWaysToDraw()->begin();
		for(int j=0;j<wayRand;j++)
			it++;
		Way* currentWay=cityMap->GetWay(*it);
		
		waySize=currentWay->GetNodes().size();
		nodeRand=rand()%(waySize-1);
		
		Street* currentStreet=currentWay->GetPortionStreet(nodeRand);
		
		SF3dVector v1,v2,vr;
		
		v1=SF3dVector(currentStreet->corners[1],currentStreet->corners[0]);
		v2=SF3dVector(currentStreet->corners[1],currentStreet->corners[2]);
		int heightLevel=rand()%4;
		if(heightLevel==0)
			v1=v1*0.05;
		else
			if(heightLevel==1)
				v1=v1*0.25;
			else
				if(heightLevel==2)
					v1=v1*0.75;
				else
					if(heightLevel==4)
						v1=v1*0.95;
		v2=v2*((rand()%100)/100.0);
		vr=v1+v2;
		vr.x+=currentStreet->corners[1].x;
		vr.y+=currentStreet->corners[1].y;
		vr.z+=currentStreet->corners[1].z;
		Point objectCenter(vr.x,vr.y,vr.z);
		long angle=atan2(v2.z,v2.x)+PI/2;
		invisiblePool[i]->SetAngle(angle*180/PI+(180*(rand()%2)));
		invisiblePool[i]->setCenter(objectCenter);
		
		visiblePoolHuman.push_back(invisiblePool[i]);		
	}
	invisiblePoolHuman.clear();
}

void WorldGenerator::Draw()
{
	for(int i=0;i<visiblePoolHuman.size();i++)
		((Human*)visiblePoolHuman[i])->Draw();
}
WorldGenerator::~WorldGenerator()
{
	visiblePoolHuman.erase(visiblePoolHuman.begin(),visiblePoolHuman.end());
	invisiblePoolHuman.erase(invisiblePoolHuman.begin(),invisiblePoolHuman.end());
	visiblePoolCar.erase(visiblePoolCar.begin(),visiblePoolCar.end());
	invisiblePoolCar.erase(invisiblePoolCar.begin(),invisiblePoolCar.end());
}
