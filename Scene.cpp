#include "Scene.h"
#include "Drawable.h"

Scene::Scene(Model *model,CCamera *cam)
	:model(model),cam(cam)
{
}
void Scene::Render()
{
	if(cam)
		cam->Render();

	std::vector<Drawable*> *sceneObjects=model->GetSceneObjects();
	for (std::vector<Drawable*>::iterator it = sceneObjects->begin(); it != sceneObjects->end(); ++it)
		(*it)->Draw();
}
Scene::~Scene(void)
{
}
