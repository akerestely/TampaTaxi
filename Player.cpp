#include "Player.h"

Player::Player(Car* car)
	:car(car)
{
	HasClient = false;
	Client = NULL;
	CheckpointGenerated = false;
}

void Player::Draw()
{
	if(car != NULL)
		car->Draw();
}

Car* Player::GetCar()
{
	if(car != NULL)
		return car;
	return NULL;
}

Collidable* Player::GetPlayerState()
{
	if(car != NULL)
		return car;
	return NULL;
}
Point Player::GetPosition()
{
	if(car != NULL)
		return car->GetCenter();
	return Point();
}
//void SetCheckpoint(Point carCheckpoint, Point humanCheckpoint)
//{
//
//}
//void SetClient(Human* client)
//{
//
//}

Player::~Player(void)
{
}
