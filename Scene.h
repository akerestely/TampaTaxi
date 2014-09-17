#pragma once
#include <vector>
#include "Drawable.h"
class Scene
{
	std::vector<Drawable*> sceneObjects;
public:
	Scene(void);
	void AddObject(Drawable *obj);
	void Render();
	//void Update();
	~Scene(void);
};
