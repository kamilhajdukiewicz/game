#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "sceneobject.h"

class Player : public SceneObject
{
public:
	static Player* getInstance();
private:
	static Player* instance;
	Player();
	~Player();
public:
	void Render();
	void Update();

	vec3 dir;
	float speed;
	
	float velocity_vertical;
	float velocity_horizontal;

	bool flyingMode;

	float fuel;
	float maxFuel;

	int hp;
	int score;
};

#endif // !PLAYER_H
