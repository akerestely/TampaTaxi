#include "Model.h"

Model::Model(void)
{
}

std::vector<Drawable*>* Model::GetSceneObjects()
{
	return &sceneObjects;
}
Player Model::GetPlayer()
{
	return *player;
}
void Model::Update()
{
	sceneObjects.clear();
	sceneObjects.push_back(&skyCube);
	//skyCube.SetPoz(Point(cam.GetPosition().x,0,cam.GetPosition().z));
	/*for(int i=0;i<buildings.size();i++) 
	   buildings[i].SwitchMode(cam.GetPosition(), -cam.GetRotY());*/
}
Model::~Model(void)
{
}
