#pragma once
#include "Human.h"
#include "Car.h"

class Player : public Drawable
{
	Car* car;
	
public:
	int LastVisitedNodeIndex;
	bool HasClient, CheckpointGenerated;
	Point CarCheckpoint, HumanCheckpoint;
	Human* Client;

	Player(Car* car);
	void Draw();
	Car* GetCar();
	Point GetPosition();
	void SetPosition(Point p);
	Collidable* GetPlayerState();
	//void SetCheckpoint(Point carCheckpoint, Point humanCheckpoint);
	//void SetClient(Human* client);
	~Player(void);
};


