#pragma once
#include "Model.h"
class Scene
{
	Model *model;
public:
	Scene(Model *model);
	void Render();
	~Scene(void);
};
