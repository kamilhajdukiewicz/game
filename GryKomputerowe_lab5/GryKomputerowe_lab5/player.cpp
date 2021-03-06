#include "stdafx.h"
#include "player.h"
Player* Player::instance = NULL;
Player * Player::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Player();
	}
	return instance;
}

Player::Player()
{
	pos.x = 3.0f;
	pos.y = 3.0f;
	pos.z = 10.0f;

	dir.x = 0.0f;
	dir.y = 0.0f;
	dir.z = -1.0f;

	speed = 0.15f;
	radius = 0.5f;

	velocity_horizontal = 0;
	velocity_vertical = 0;

	weight = 2;

	hp = 100;
	fuel = 100;
	maxFuel = 100;
	score = 0;
}

void Player::Render() {};

void Player::Update()
{
	pos.y = 3.0f;

	pos.x += dir.x * speed * velocity_vertical;
	pos.z += dir.z * speed * velocity_vertical;

	pos.x += dir.z * speed * velocity_horizontal;
	pos.z -= dir.x * speed * velocity_horizontal;

	velocity_vertical /= 1.2;
	velocity_horizontal /= 1.2;

	pos.x += force.x / weight;
	//pos.y += force.y / weight;
	pos.z += force.z / weight;

	force.x /= 1.2;
	//force.y /= 1.2;
	force.z /= 1.2;

	fuel -= 0.1f;

	if (fuel > maxFuel)
		fuel = maxFuel;
}