#pragma once
#include <vector>
#include "CameraSpectator.h"
#include "SkyCube.h"
#include "Human.h"
#include "Car.h"
#include "Map.h"
#include "Player.h"

class Model
{
	std::vector<Drawable*> sceneObjects;
	SkyCube skyCube;
	CCamera camera;
	Human* human;
	Map* brasovMap;
	Car* car;
	Player *player;

	std::vector<Collidable *> collidables;
public:
	Model(void);
	std::vector<Drawable*>* GetSceneObjects();
	CCamera GetCamera();
	void Update();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void MouseMove(double dx,double dy);
	~Model(void);
};
