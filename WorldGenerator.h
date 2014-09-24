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
	void UpdateVector(std::vector<Collidable*>& invisibleVector);
	bool checkVisibles(Point currentPosition);
	void Draw();
	~WorldGenerator();
};
