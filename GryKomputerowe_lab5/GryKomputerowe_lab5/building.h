#pragma once
#ifndef BUILDING_H
#define BUILDING_H

#include "stdafx.h"
#include "sceneobject.h"

class Building : public SceneObject
{
public:
	Building(vec3 pos, vec3 color, float size, std::string textureName = "");
	~Building();

	void Render();
	void Update();

	float size;

	std::string textureName;

	float uvMultipler;
};

#endif
