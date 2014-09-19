#pragma once
#include <vector>
#include "CameraSpectator.h"
#include "SkyCube.h"
#include "Ball.h"
#include "Human.h"
#include "Map.h"

class Model
{
	std::vector<Drawable*> sceneObjects;
	SkyCube skyCube;
	CCamera camera;
	Ball *ball;
	Human *human;
	Map *brasovMap;
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
