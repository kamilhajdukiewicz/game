#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include "vec3.h"

#define PI 3.14159265359

class SceneObject
{
public:
	SceneObject();
	~SceneObject();

	vec3 pos;
	vec3 prevPos;

	vec3 force;
	float weight;
	float radius;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	bool isAlive;

	virtual void Render() = 0;
	virtual void Update() = 0;

};


#endif

