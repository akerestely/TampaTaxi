#include "Scene.h"

Scene::Scene(void)
{
}
void Scene::Render()
{
	for (std::vector<Drawable*>::iterator it = sceneObjects.begin(); it != sceneObjects.end(); ++it)
		(*it)->Draw();
}
void Scene::AddObject(Drawable *obj)
{
	sceneObjects.push_back(obj);
}
Scene::~Scene(void)
{
}
