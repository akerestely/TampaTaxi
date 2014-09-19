#include "Model.h"

#define SPEED 10

Model::Model(void)
{
	ball=new Ball(0.5,Point(0,0,0));
	ball->SetTexNr(0);
	brasovMap = new Map("OnlyStreetsFinal.osm", "Buildings.xml");
}

std::vector<Drawable*>* Model::GetSceneObjects()
{
	return &sceneObjects;
}
CCamera Model::GetCamera()
{
	return camera;
}
void Model::Update()
{
	sceneObjects.clear();
	sceneObjects.push_back(&skyCube);
	sceneObjects.push_back(ball);
	sceneObjects.push_back(brasovMap);

	skyCube.SetPoz(camera.GetPosition());
	brasovMap->Update(camera.GetPosition());
	/*for(int i=0;i<buildings.size();i++) 
	   buildings[i].SwitchMode(cam.GetPosition(), -cam.GetRotY());*/
}
void Model::MoveUp()
{
	SF3dVector v = camera.MoveZ(-SPEED);
	ball->MoveX(v.x);
	ball->MoveZ(v.z);
}
void Model::MoveDown()
{
	SF3dVector v = camera.MoveZ(SPEED);
	ball->MoveX(v.x);
	ball->MoveZ(v.z);
}
void Model::MoveLeft()
{
	SF3dVector v = camera.MoveX(-SPEED);
	ball->MoveX(v.x);
	ball->MoveZ(v.z);
}
void Model::MoveRight()
{
	SF3dVector v = camera.MoveX(+SPEED);
	ball->MoveX(v.x);
	ball->MoveZ(v.z);
}
void Model::MouseMove(double dx,double dy)
{
	double rotY=dx*0.12;
	double rotX=dy*0.12;
	camera.RotateY(rotY);
	camera.RotateX(rotX);
}
Model::~Model(void)
{
	delete ball;
}
