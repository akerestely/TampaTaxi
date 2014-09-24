#include "Model.h"

#define SPEED 0.3

Model::Model(void)
{
	human= new Human(Point(-13, 0, 13));
	car= new Car(Point());

	//brasovMap = new Map("OnlyStreetsFinal.osm", "BuildingsV2.osm");

	player = new Player(car);
	player->LastVisitedNodeIndex = START_NODE;

	wg = new WorldGenerator(brasovMap);
	wg->Initialize();
	
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


Player* Model::GetPlayer()
{
	return player;
}
void Model::Update()
{
	sceneObjects.clear();
	sceneObjects.push_back(&skyCube);
	sceneObjects.push_back(human);
	sceneObjects.push_back(car);
	//sceneObjects.push_back(brasovMap);
	//sceneObjects.push_back(wg);
	
	camera.SetPosition(player->GetPosition());

	car->Update();
	skyCube.SetPoz(camera.GetPosition());
	//brasovMap->Update(camera.GetPosition(), camera.GetRotY());

	//wg->Update();
}
void Model::MoveUp()
{
	car->Accelerate();
	/*car->SetAngle(camera.GetRotY());
	if(car->MoveWith(-5))
	{
		if(!playerMapCollision())
			car->MoveWith(5);
	}*/
	
		
}
void Model::MoveDown()
{
	car->Reverse();
	/*car->SetAngle(camera.GetRotY());
	if(car->MoveWith(5))
	{
		if(!playerMapCollision())
			car->MoveWith(-5);
	}*/
}
void Model::MoveLeft()
{
	car->TurnLeft();
	/*SF3dVector v = camera.MoveX(-SPEED);*/
}
void Model::MoveRight()
{
	car->TurnRight();
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
int Model::playerMapCollision()
{
	int insidePoints = 0;
	Point M;

	Collidable* collidable = player->GetPlayerState();
	if(collidable == NULL)
		return 0;
	
	
	
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
		
		Node* lastVisitedNode = brasovMap->GetNode(player->LastVisitedNodeIndex);
		insidePoints += playerStreetCollision(lastVisitedNode, M);
		if (insidePoints != i + 1)
		{
			std::vector<long> adjacentWays = lastVisitedNode->GetWays();
			for(int adjW = 0; adjW < adjacentWays.size() && insidePoints != i + 1; adjW++)
			{
				Way* adjacentWay = brasovMap->GetWay(adjacentWays[adjW]);
				int nodeWayIndex = adjacentWay->GetIndex(lastVisitedNode);
				
				Node *node = adjacentWay->GetNode(nodeWayIndex - 1);
				if (node != NULL)
					insidePoints += playerStreetCollision(node, M);
				
				if(insidePoints != i + 1)
				{
					node = adjacentWay->GetNode(nodeWayIndex + 1);
					if(node != NULL)
						insidePoints += playerStreetCollision(node, M);
					if (insidePoints == i + 1)
						player->LastVisitedNodeIndex = node->GetId();
				}
				else
					player->LastVisitedNodeIndex = node->GetId();
			}
		}
		if (insidePoints != i + 1)
			break;
	}
	if(insidePoints == 4)
		return 1;
	return 0;
}
int Model::playerStreetCollision(Node *node, Point M)
{
	Point nodeCenter = node->GetCenter();
	if(Tools::PointInsideCircle(M, nodeCenter, NODE_DIAMETER / 2))
		return 1;
	
	std::vector<long> adjacentWays = node->GetWays();
	for(int adjW = 0; adjW < adjacentWays.size(); adjW++)
	{
		Way* adjacentWay = brasovMap->GetWay(adjacentWays[adjW]);
		int nodeWayIndex = adjacentWay->GetIndex(node);
		Street *portionStreet = adjacentWay->GetPortionStreet(nodeWayIndex);
		if(portionStreet != NULL && Tools::PointInsideRectangle(M, portionStreet->corners[0], portionStreet->corners[1], portionStreet->corners[2], portionStreet->corners[3]))
		{
			return 1;
		}
		portionStreet = adjacentWay->GetPortionStreet(nodeWayIndex - 1);
		if(portionStreet != NULL && Tools::PointInsideRectangle(M, portionStreet->corners[0], portionStreet->corners[1], portionStreet->corners[2], portionStreet->corners[3]))
		{
			return 1;
		}
	}	
	return 0;
}
Model::~Model(void)
{
	//delete brasovMap;
}
