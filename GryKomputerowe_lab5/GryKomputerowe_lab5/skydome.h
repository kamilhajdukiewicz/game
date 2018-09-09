#pragma once
#ifndef SKYDOME_H
#define SKYDOME_H

#include <string>
#include "vec3.h"

class Skydome
{
public:
	Skydome(float radius, std::string textureName);
	~Skydome();

	void Render();
	void Update();

	int frameCounter;
	float radius;
	std::string textureName;
	vec3 position;
};


#endif 