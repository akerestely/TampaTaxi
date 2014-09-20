#pragma once
#include <vector>
#include "CameraSpectator.h"
#include "SkyCube.h"
#include "Ball.h"
#include "Human.h"
#include "Car.h"
#include "Map.h"

class Model
{
	std::vector<Drawable*> sceneObjects;
	SkyCube skyCube;
	CCamera camera;
	Ball* ball;
	Human* human;
	Map* brasovMap;
	Car* car;

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
