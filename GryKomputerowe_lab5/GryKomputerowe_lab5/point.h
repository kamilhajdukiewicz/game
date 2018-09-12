#pragma once
#include "stdafx.h"
#include "sceneobject.h"
#include "vec3.h"

class Point : public SceneObject
{
public:
	Point(vec3 pos, vec3 color, float radius, float weight);
	~Point(void);

	void Render();
	void Update();

	void isColid(float x, float z, float x2, float z2);

	float radiusChangePerUpdate;
};
