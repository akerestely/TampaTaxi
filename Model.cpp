#include "Model.h"

#define SPEED 0.3

Model::Model(void)
{
	camera = new CCamera(20.0);

	brasovMap = new Map("StreetsRefactor.osm", "BuildingsRefactor.osm");
	worldGenerator = new WorldGenerator(brasovMap);
	worldGenerator->Initialize();

	car = new Car(Point());
	car->colliders=worldGenerator->GetVisibleCars();

	player = new Player(car);
	player->LastVisitedNodeIndex = START_NODE;
}

void Model::Update()
{
	sceneObjects.clear();
	sceneObjects.push_back(&skyCube);
	sceneObjects.push_back(car);
	sceneObjects.push_back(brasovMap);
	sceneObjects.push_back(worldGenerator);
	
	camera->SetPosition(player->GetPosition());

	car->Update();
	if(!playerMapCollision())
		car->Undo();

	skyCube.SetPoz(player->GetPosition());
	brasovMap->Update(player->GetPosition(), camera->GetRotY());

	if(player->GetPosition() == player->CarCheckpoint && car->GetSpeed() == 0 && player->HasClient == true)
	{
		player->HasClient = false;
		player->CheckpointGenerated = false;
		Human *client = player->Client;
		client->setCenter(player->HumanCheckpoint);
		player->Client = NULL;
		
	}
	worldGenerator->Update(player->GetPosition());
	worldGenerator->HumanCallTaxi(player);
	if (player->HasClient && player->CheckpointGenerated == false)
	{
		Point carCheckpoint, humanCheckpoint;
		brasovMap->GenerateCheckpoint(2000, carCheckpoint, humanCheckpoint);
		player->CarCheckpoint = carCheckpoint;
		player->HumanCheckpoint = humanCheckpoint;
		player->CheckpointGenerated = true;
	}
	for(std::vector<Collidable*>::iterator it=worldGenerator->GetVisibleHumans()->begin();it<worldGenerator->GetVisibleHumans()->end();++it)
		((Human*)(*it))->Update();
}
void Model::MoveUp()
{
	car->Accelerate();
}
void Model::MoveDown()
{
	car->Reverse();
}
void Model::MoveLeft()
{
	car->TurnLeft();
}
void Model::MoveRight()
{
	car->TurnRight();
}
void Model::MouseMove(double dx,double dy)
{
	double rotY=dx*0.12;
	double rotX=dy*0.12;
	camera->RotateY(rotY);
	camera->RotateX(rotX);
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
		brasovMap->StreetCollision(lastVisitedNode, M, insidePoints);
		if (insidePoints != i + 1)
		{
			std::vector<long> adjacentWays = lastVisitedNode->GetWays();
			for(int adjW = 0; adjW < adjacentWays.size() && insidePoints != i + 1; adjW++)
			{
				Way* adjacentWay = brasovMap->GetWay(adjacentWays[adjW]);
				int nodeWayIndex = adjacentWay->GetIndex(lastVisitedNode);
				
				Node *node = adjacentWay->GetNode(nodeWayIndex - 1);
				if (node != NULL)
					brasovMap->StreetCollision(node, M, insidePoints);
				
				if(insidePoints != i + 1)
				{
					node = adjacentWay->GetNode(nodeWayIndex + 1);
					if(node != NULL)
						brasovMap->StreetCollision(node, M, insidePoints);
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

std::vector<Drawable*>* Model::GetSceneObjects()
{
	return &sceneObjects;
}

CCamera Model::GetCamera()
{
	return *camera;
}

Player* Model::GetPlayer()
{
	return player;
}

Map* Model::GetMap()
{
	return brasovMap;
}

Model::~Model(void)
{
	delete brasovMap;
}
