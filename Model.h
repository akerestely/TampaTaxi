#pragma once
#include <vector>
#include "Player.h"
#include "SkyCube.h"

class Model
{
	std::vector<Drawable*> sceneObjects;
	Player *player;
	SkyCube skyCube;
public:
	Model(void);
	std::vector<Drawable*>* GetSceneObjects();
	Player GetPlayer();
	void Update();
	~Model(void);
};
