#pragma once
#ifndef SCENE_H
#define SCENE_H

#include "sceneobject.h"


class Scene
{
public:
	Scene();
	~Scene();

	void addObject(SceneObject*);

private:
	//struct Triangle
	//{
	//	vec3 v1, v2, v3;
	//	vec3 uv1, uv2, uv3;
	//	std::string textureName;
	//	vec3 n;
	//	float A, B, C, D;
	//};

	std::vector<SceneObject*> sceneObjects;
	//std::vector<Triangle> collisionTriangles;
};
#endif // !SCENE_H
