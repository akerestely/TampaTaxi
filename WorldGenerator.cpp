#include "WorldGenerator.h"

WorldGenerator::WorldGenerator(CollidableQuadTree* collidableQuadTree,Point currentPosition)
{
	this->collidableQuadTree=collidableQuadTree;
	this->currentPosition=currentPosition;

}

void WorldGenerator::Initialize()
{
	for(int i=0;i<20;i++)
		invisiblePool.push_back(new Car(0.0,0.0,0.0));
	for(int i=0;i<30;i++)
		invisiblePool.push_back(new Human(0.0,0.0,0.0));


}

void WorldGenerator::Update()
{
	
}
WorldGenerator::~WorldGenerator()
{
	visiblePool.erase(visiblePool.begin(),visiblePool.end());
	invisiblePool.erase(invisiblePool.begin(),invisiblePool.end());
}
