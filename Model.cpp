#include "Model.h"

#define SPEED 0.3

Model::Model(void)
{
	human= new Human(Point());
	car= new Car(Point(-3,0,-13));
	//car->SetAngle(90);
	brasovMap = new Map("OnlyStreetsFinal.osm", "Buildings.xml");

	//to be deleted
	collidables.push_back(car);
	collidables.push_back(human);

	human->colliders=&collidables;
	car->colliders=&collidables;
	//to be deleted
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
	sceneObjects.push_back(human);
	sceneObjects.push_back(car);
	sceneObjects.push_back(brasovMap);
	
	camera.SetPosition(human->GetCenter());

	//car->MoveWith(-0.2);
	skyCube.SetPoz(camera.GetPosition());
	brasovMap->Update(camera.GetPosition());
}
void Model::MoveUp()
{
	human->SetAngle(camera.GetRotY());
	if(human->WalkForward())
	{
		//camera.SetPosition(car->GetCenter());
	}
}
void Model::MoveDown()
{
	human->SetAngle(camera.GetRotY());
	if(human->WalkBackward())
	{
		//camera.SetPosition(car->GetCenter());
	}
}
void Model::MoveLeft()
{
	/*SF3dVector v = camera.MoveX(-SPEED);*/
}
void Model::MoveRight()
{
	/*SF3dVector v = camera.MoveX(+SPEED);*/
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
	delete brasovMap;
}
