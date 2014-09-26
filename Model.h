#pragma once
#include <vector>
#include "CameraSpectator.h"
#include "SkyCube.h"
#include "Human.h"
#include "Car.h"
#include "Map.h"
#include "WorldGenerator.h"
#include "Player.h"

class Model
{
	std::vector<Drawable*> sceneObjects;
	SkyCube skyCube;
	CCamera *camera;
	Map* brasovMap;
	Car* car;
	Player* player;

	WorldGenerator *worldGenerator;

	int playerMapCollision();
	
public:
	Model(void);
	std::vector<Drawable*>* GetSceneObjects();
	CCamera GetCamera();
	Player* GetPlayer();
	void Update();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Jump();
	void MouseMove(double dx,double dy);
	void SetStartingPoint(long id);
	Map* GetMap();
	~Model(void);
};
