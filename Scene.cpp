#include "Scene.h"
#include "Drawable.h"
#include "CameraSpectator.h"

Scene::Scene(Model *model)
	:model(model)
{
}
void Scene::Render()
{
	model->GetCamera().Render();

	std::vector<Drawable*> *sceneObjects=model->GetSceneObjects();
	for (std::vector<Drawable*>::iterator it = sceneObjects->begin(); it != sceneObjects->end(); ++it)
		(*it)->Draw();
}
Scene::~Scene(void)
{
}
