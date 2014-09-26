#pragma once
#include "drawable.h"
#include"Point.h"

#include"CollidableQuadTree.h"
#include"Player.h"
#include "Car.h"
#include"Human.h"
#include"Map.h"

#include<vector>
#include<ctime>


#define MINIMUM_MAGNITUDE 150
#define OBJECT_DENSITY 15

class WorldGenerator :
	public Drawable
{
	CollidableQuadTree* collidableQuadTree;
	Map* cityMap;
	std::vector<Collidable*> invisiblePoolHuman,visiblePoolHuman;
	std::vector<Collidable*> invisiblePoolCar,visiblePoolCar;
public:
	WorldGenerator(Map* cityMap);
	void Initialize();
	void Update(Point currentPosition);
	void UpdateHumanVector(Point currentPosition);
	void UpdateCarVector(Point currentPosition);
	bool CheckVisibles(Point currentPosition);
	void HumanCallTaxi(Player* player);
	
	void Draw();

	std::vector<Collidable*>* GetVisibleHumans();
	std::vector<Collidable*>* GetVisibleCars();

	~WorldGenerator();
};
