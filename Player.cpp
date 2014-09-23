#include "Player.h"

Player::Player(Car* car)
	:car(car)
{
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
Player::~Player(void)
{
}
