#pragma once
#include "drawable.h"
#include"Point.h"

#include"CollidableQuadTree.h"
#include"Player.h"
#include "Car.h"
#include"Human.h"
#include<vector>

#define AreaRadius 100 
#define maxCars 20	
#define maxHumans 40


class WorldGenerator :
	public Drawable
{
	CollidableQuadTree* collidableQuadTree;
	Point currentPosition;
	std::vector<Collidable*> invisiblePool,visiblePool;
public:
	WorldGenerator(CollidableQuadTree* collidableQuadTree,Point currentPosition);
	void Initialize();
	void Update();
	~WorldGenerator();
};
