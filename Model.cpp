#include "Model.h"

#define SPEED 0.3

Model::Model(void)
{
	human= new Human(Point(-13, 0, 13));
	
	//car->SetAngle(90);
	brasovMap = new Map("OnlyStreetsFinal.osm", "BuildingsV2.osm");

	car= new Car(Point());
	player = new Player(car);
	player->LastVisitedNodeIndex = START_NODE;

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
	
	camera.SetPosition(player->GetPosition());

	/*car->Update();*/
	skyCube.SetPoz(camera.GetPosition());
	brasovMap->Update(camera.GetPosition());
}
void Model::MoveUp()
{
	car->SetAngle(camera.GetRotY());
	if(car->MoveWith(-5))
	{
		if(!playerStreetCollision())
			car->MoveWith(5);
	}
	
		
}
void Model::MoveDown()
{
	car->SetAngle(camera.GetRotY());
	if(car->MoveWith(5))
	{
		if(!playerStreetCollision())
			car->MoveWith(-5);
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

int Model::playerStreetCollision()
{
	int insidePoints = 0;

	Collidable* collidable = player->GetPlayerState();
	if(collidable == NULL)
		return 0;
	Node* lastVisitedNode = brasovMap->GetNode(player->LastVisitedNodeIndex);
	std::vector<long> adjacentWays = lastVisitedNode->GetWays();
	Point nodeCenter = lastVisitedNode->GetCenter();
	Point M;
	
	for(int i = 0; i < 4; i++)
	{
		if(i == 0)
			M = collidable->GetTopRight();
		if(i == 1)
			M = collidable->GetBottomRight();
		if(i == 2)
			M = collidable->GetBottomLeft();
		if(i == 3)
			M = collidable->GetTopLeft();
		if(Tools::PointInsideCircle(M, nodeCenter, NODE_DIAMETER / 2))
		{
			insidePoints++;
			continue;
		}
		for(int adjW = 0; adjW < adjacentWays.size(); adjW++)
		{
			Way* adjacentWay = brasovMap->GetWay(adjacentWays[adjW]);
			int nodeWayIndex = adjacentWay->GetIndex(lastVisitedNode);
			Street *portionStreet = adjacentWay->GetPortionStreet(nodeWayIndex);
			if(portionStreet != NULL && Tools::PointInsideRectangle(M, portionStreet->corners[0], portionStreet->corners[1], portionStreet->corners[2], portionStreet->corners[3]))
			{
				insidePoints++;
				break;
			}
			portionStreet = adjacentWay->GetPortionStreet(nodeWayIndex - 1);
			if(portionStreet != NULL && Tools::PointInsideRectangle(M, portionStreet->corners[0], portionStreet->corners[1], portionStreet->corners[2], portionStreet->corners[3]))
			{
				insidePoints++;
				break;
			}
			Node *node = adjacentWay->GetNode(nodeWayIndex - 1);
			if(node != NULL && Tools::PointInsideCircle(M, node->GetCenter(), NODE_DIAMETER / 2))
			{
				insidePoints++;
				player->LastVisitedNodeIndex = node->GetId();
				return playerStreetCollision();
				//break;
			}
			node = adjacentWay->GetNode(nodeWayIndex + 1);
			if(node != NULL && Tools::PointInsideCircle(M, node->GetCenter(), NODE_DIAMETER / 2))
			{
				insidePoints++;
				player->LastVisitedNodeIndex = node->GetId();
				return playerStreetCollision();
				//break;
			}
		}		
	}
	if(insidePoints == 4)
		return 1;
	return 0;
}
Model::~Model(void)
{
	delete brasovMap;
}
