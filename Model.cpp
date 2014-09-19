#include "Model.h"

#define SPEED 0.3

Model::Model(void)
{
	ball=new Ball(0.5,Point(0,0,0));
	ball->SetTexNr(0);
	human=new Human(Point());
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
	//sceneObjects.push_back(ball);
	sceneObjects.push_back(human);
	human->setWalk(false);
	sceneObjects.push_back(brasovMap);

	skyCube.SetPoz(camera.GetPosition());
	brasovMap->Update(camera.GetPosition());
}
void Model::MoveUp()
{
	SF3dVector v = camera.MoveZ(-SPEED);
	ball->MoveX(v.x);
	ball->MoveZ(v.z);
	human->SetAngle(camera.GetRotY());
	human->MoveWith(-SPEED);
	human->setWalk(true);
}
void Model::MoveDown()
{
	SF3dVector v = camera.MoveZ(SPEED);
	ball->MoveX(v.x);
	ball->MoveZ(v.z);
	human->SetAngle(camera.GetRotY());
	human->MoveWith(+SPEED);
	human->setWalk(true);
}
void Model::MoveLeft()
{
	/*SF3dVector v = camera.MoveX(-SPEED);
	ball->MoveX(v.x);
	ball->MoveZ(v.z);*/
}
void Model::MoveRight()
{
	/*SF3dVector v = camera.MoveX(+SPEED);
	ball->MoveX(v.x);
	ball->MoveZ(v.z);*/
}
void Model::MouseMove(double dx,double dy)
{
	double rotY=dx*0.12;
	double rotX=dy*0.12;
	camera.RotateY(rotY);
	camera.RotateX(rotX);
	//human->IncrementAngle(rotY);
}
Model::~Model(void)
{
	delete ball;
}
