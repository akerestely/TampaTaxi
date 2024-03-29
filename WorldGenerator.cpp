#include "WorldGenerator.h"
#include<math.h>

#define MINIMUM_MAGNITUDE 150
#define OBJECT_DENSITY 15
#define MAX_DISTANCE 50
#define MIN_DISTANCE 5

WorldGenerator::WorldGenerator(Map* cityMap)
{
	this->cityMap=cityMap;
}

void WorldGenerator::Initialize()
{
	for(int i=0;i<OBJECT_DENSITY;i++)
	{
		Human *h=new Human(Point(0.0,0.0,0.0));
		h->colliders=&visiblePoolHuman;
		invisiblePoolHuman.push_back(h);
		invisiblePoolCar.push_back(new Car(Point(0.0,0.0,0.0)));
	}
	srand(time(NULL));
}

void WorldGenerator::Update(Point currentPosition)
{	
//Human & Car testing
	CheckVisibles(currentPosition);
	
//Updating visible objects 
	UpdateHumanVector(currentPosition);
	UpdateCarVector(currentPosition);	
}

void WorldGenerator::UpdateHumanVector(Point currentPosition)
{
	int i=0;
	long randNumber;
	int setSize, wayRand, nodeRand, waySize;
	while(i<invisiblePoolHuman.size())
	{	
		randNumber = rand();
		setSize=cityMap->GetWaysToDraw()->size();
		wayRand,nodeRand;
		waySize;
		wayRand = randNumber%setSize;
		std::set<long>::iterator it=cityMap->GetWaysToDraw()->begin();
		std::advance(it, wayRand);

		Way* currentWay=cityMap->GetWay(*it);
		waySize=currentWay->GetNodes().size();
		nodeRand = randNumber % (waySize - 1);
		int sideRand = randNumber % 2;
		Street* currentStreet;
		if(sideRand==0)
		{
			currentStreet=currentWay->GetLeftSidewalk(nodeRand);
			
		}
		else
		{ 
			currentStreet=currentWay->GetRightSidewalk(nodeRand);
		}
		
		SF3dVector v1,v2,vr;

		v1=SF3dVector(currentStreet->corners[1],currentStreet->corners[0]);
		v2=SF3dVector(currentStreet->corners[1],currentStreet->corners[2]);
		v1=v1*0.50;
		vr=v1+v2*(((rand()%41)+30.0)/100.0);
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
			SF3dVector lim1=v1+v2*0.2;
			SF3dVector lim2=v1+v2*0.8;
		
			((Human*)(invisiblePoolHuman[i]))->setLimits(lim1.ToPoint()+currentStreet->corners[1],lim2.ToPoint()+currentStreet->corners[1]);

			visiblePoolHuman.push_back(invisiblePoolHuman[i]);	
			invisiblePoolHuman.erase(invisiblePoolHuman.begin()+i);
		}
		else i++;


	}
}

void WorldGenerator::UpdateCarVector(Point currentPosition)
{
	int i=0;
	int randNumber;
	int setSize, wayRand, nodeRand, waySize;
	while(i<invisiblePoolCar.size())
	{	
		randNumber = rand();
		setSize=cityMap->GetWaysToDraw()->size();
		
		wayRand = randNumber % setSize;
		std::set<long>::iterator it=cityMap->GetWaysToDraw()->begin();
		std::advance(it, wayRand);
		
		Way* currentWay=cityMap->GetWay(*it);

		waySize=currentWay->GetNodes().size();
		nodeRand = randNumber % (waySize - 1);

		Street* currentStreet=currentWay->GetPortionStreet(nodeRand);
	
		SF3dVector v1,v2,vr;

		v1=SF3dVector(currentStreet->corners[1],currentStreet->corners[0]);
		v2=SF3dVector(currentStreet->corners[1],currentStreet->corners[2]);
		
		int heightLevel = randNumber % 2;
		if(heightLevel==0)
			v1=v1*0.15;
		else
			if(heightLevel==1)
				v1=v1*0.85;
			
			v2 = v2*((randNumber % 100) / 100.0);
		vr=v1+v2;
		vr.x+=currentStreet->corners[1].x;
		vr.y+=currentStreet->corners[1].y;
		vr.z+=currentStreet->corners[1].z;
		Point objectCenter(vr.x,vr.y,vr.z);
		SF3dVector checkDistance(currentPosition,objectCenter);
		if(checkDistance.GetMagnitude()>MINIMUM_MAGNITUDE)
		{
		double angle=atan2(-v2.z,v2.x)+PI/2;
		if(heightLevel==0)
			invisiblePoolCar[i]->SetAngle(angle*180/PI+180);
		else
			invisiblePoolCar[i]->SetAngle(angle*180/PI);
		//invisiblePoolCar[i]->SetAngle(resultAngle*180/PI+(180*(rand()%2)));
		invisiblePoolCar[i]->setCenter(objectCenter);
		visiblePoolCar.push_back(invisiblePoolCar[i]);
		invisiblePoolCar.erase(invisiblePoolCar.begin()+i);
		}
		else i++;
	}
}


bool WorldGenerator::CheckVisibles(Point currentPosition)
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
			i--;
		}
		else
			if(((Human*)(visiblePoolHuman[i]))->GetInTaxi()==true)
			{
				invisiblePoolHuman.push_back(visiblePoolHuman[i]);
				visiblePoolHuman.erase(visiblePoolHuman.begin()+i);
				changed=true;
				i--;
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

void WorldGenerator::HumanCallTaxi(Player* player)                        
{
	for(std::vector<Collidable*>::iterator it=visiblePoolHuman.begin();it<visiblePoolHuman.end();++it)
	{
		if(player->HasClient==false)
		{
			SF3dVector distHumanTaxi((*it)->GetCenter(),player->GetPosition());
			double distance=distHumanTaxi.GetMagnitude();
			if( distance > MIN_DISTANCE && distance < MAX_DISTANCE )
			{
				
				if(((Human*)(*it))->GetCallTaxi()==false)
				{
					if (rand() % 1000 == 1)
						((Human*)(*it))->SetCallTaxi(true);
				}
				if(((Human*)(*it))->GetCallTaxi()==true)
				{
					SF3dVector viewThePlayer((*it)->GetCenter(),player->GetPosition());
					((Human*)(*it))->SetViewDir(viewThePlayer.GetNormalized());
				}
			}
			else if(distance <= MIN_DISTANCE && player->GetCar()->GetSpeed() < 0.05 && player->GetCar()->GetSpeed() > -0.05)
			{
				Human* client = (Human*)(*it);
				client->SetInTaxi(true);
				player->HasClient=true;
				player->Client = client;
				
			}
				else if(distance >= MAX_DISTANCE)
				{
					if(((Human*)(*it))->GetCallTaxi())
						((Human*)(*it))->SetCallTaxi(false);
				}
		}
		else
		{
			if(((Human*)(*it))->GetCallTaxi())
				((Human*)(*it))->SetCallTaxi(false);
		}
	}
}

std::vector<Collidable*>* WorldGenerator::GetVisibleHumans()
{
	return &visiblePoolHuman;
}

std::vector<Collidable*>* WorldGenerator::GetVisibleCars()
{
	return &visiblePoolCar;
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