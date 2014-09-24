#include "WorldGenerator.h"
#include<math.h>

WorldGenerator::WorldGenerator(Map* cityMap)
{
	this->cityMap=cityMap;
}

void WorldGenerator::Initialize()
{
	for(int i=0;i<OBJECT_DENSITY;i++)
	{
		invisiblePoolHuman.push_back(new Human(Point(0.0,0.0,0.0)));
		invisiblePoolCar.push_back(new Car(Point(0.0,0.0,0.0)));
	}
	srand(time(NULL));
}

void WorldGenerator::Update(Point currentPosition)
{	
//Human & Car testing
	checkVisibles(currentPosition);
//Updating visible objects 
	UpdateHumanVector(currentPosition);
	UpdateCarVector(currentPosition);	
}

void WorldGenerator::UpdateHumanVector(Point currentPosition)
{
	int i=0;
	while(i<invisiblePoolHuman.size())
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
		int sideRand=rand()%2;
		Street* currentStreet;
		if(sideRand==0)
			 currentStreet=currentWay->GetLeftSidewalk(nodeRand);
		else
			 currentStreet=currentWay->GetRightSidewalk(nodeRand);
		
		SF3dVector v1,v2,vr;

		v1=SF3dVector(currentStreet->corners[1],currentStreet->corners[0]);
		v2=SF3dVector(currentStreet->corners[1],currentStreet->corners[2]);
		v1=v1*0.50;
		v2=v2*(((rand()%41)+30.0)/100.0);
		vr=v1+v2;
		vr.x+=currentStreet->corners[1].x;
		vr.y+=currentStreet->corners[1].y;
		vr.z+=currentStreet->corners[1].z;
		Point objectCenter(vr.x,vr.y,vr.z);
		SF3dVector checkDistance(currentPosition,objectCenter);
		if(checkDistance.GetMagnitude()>MINIMUM_MAGNITUDE)
		{
			double angle=atan2(v2.z,-v2.x)+PI/2;
			invisiblePoolHuman[i]->SetAngle(angle*180/PI+(180*(rand()%2)));
			invisiblePoolHuman[i]->setCenter(objectCenter);
			visiblePoolHuman.push_back(invisiblePoolHuman[i]);	
			invisiblePoolHuman.erase(invisiblePoolHuman.begin()+i);
		}
		else i++;
	}
}

void WorldGenerator::UpdateCarVector(Point currentPosition)
{
	int i=0;
	while(i<invisiblePoolCar.size())
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
	/*	SF3dVector RESULT(currentWay->GetNode(nodeRand)->GetCenter(),
			currentWay->GetNode(nodeRand+1)->GetCenter());
			
		long resultAngle=atan2(RESULT.z,-RESULT.x)+PI/2;*/
		SF3dVector v1,v2,vr;

		v1=SF3dVector(currentStreet->corners[1],currentStreet->corners[0]);
		v2=SF3dVector(currentStreet->corners[1],currentStreet->corners[2]);
		
		int heightLevel=rand()%2;
		if(heightLevel==0)
			v1=v1*0.15;
		else
			if(heightLevel==1)
				v1=v1*0.85;
			
		v2=v2*((rand()%100)/100.0);
		vr=v1+v2;
		vr.x+=currentStreet->corners[1].x;
		vr.y+=currentStreet->corners[1].y;
		vr.z+=currentStreet->corners[1].z;
		Point objectCenter(vr.x,vr.y,vr.z);
		SF3dVector checkDistance(currentPosition,objectCenter);
		if(checkDistance.GetMagnitude()>MINIMUM_MAGNITUDE)
		{
		double angle=atan2(-v2.z,v2.x)+PI/2;
		invisiblePoolCar[i]->SetAngle(angle*180/PI+(180*(rand()%2)));
		//invisiblePoolCar[i]->SetAngle(resultAngle*180/PI+(180*(rand()%2)));
		invisiblePoolCar[i]->setCenter(objectCenter);
		visiblePoolCar.push_back(invisiblePoolCar[i]);
		invisiblePoolCar.erase(invisiblePoolCar.begin()+i);
		}
		else i++;
	}
}


bool WorldGenerator::checkVisibles(Point currentPosition)
{
	bool changed=false;
	for(int i=0;i<visiblePoolHuman.size();i++)
	{
		SF3dVector tempVector(currentPosition,visiblePoolHuman[i]->GetCenter());
		if(tempVector.GetMagnitude()>500)
		{
			invisiblePoolHuman.push_back(visiblePoolHuman[i]);
			visiblePoolHuman.erase(visiblePoolHuman.begin()+i);
			changed=true;
		}
	}
	for(int i=0;i<visiblePoolCar.size();i++)
	{
		SF3dVector tempVector(currentPosition,visiblePoolCar[i]->GetCenter());
		if(tempVector.GetMagnitude()>1000)
		{
			invisiblePoolCar.push_back(visiblePoolCar[i]);
			visiblePoolCar.erase(visiblePoolCar.begin()+i);
			changed=true;
		}
	}
	return changed;
}
void WorldGenerator::Draw()
{
	for(std::vector<Collidable*>::iterator it=visiblePoolHuman.begin();it<visiblePoolHuman.end();++it)
		((Human*)(*it))->Draw();
	for(std::vector<Collidable*>::iterator it=visiblePoolCar.begin();it<visiblePoolCar.end();++it)
		((Car*)(*it))->Draw();
}
WorldGenerator::~WorldGenerator()
{
	for(int i=0;i<visiblePoolHuman.size();i++)
	{
		delete visiblePoolHuman[i];
	}
	for(int i=0;i<invisiblePoolHuman.size();i++)
	{
		delete invisiblePoolHuman[i];
	}
	for(int i=0;i<visiblePoolCar.size();i++)
	{
		delete visiblePoolCar[i];
	}
	for(int i=0;i<invisiblePoolCar.size();i++)
	{
		delete invisiblePoolCar[i];
	}
	visiblePoolHuman.clear();
	invisiblePoolHuman.clear();
	visiblePoolCar.clear();
	invisiblePoolCar.clear();
}
