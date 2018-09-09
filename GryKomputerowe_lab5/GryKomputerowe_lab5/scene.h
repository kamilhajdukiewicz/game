#pragma once
#ifndef SCENE_H
#define SCENE_H

#include "sceneobject.h"
#include "skydome.h"


class Scene
{
public:
	Scene();
	~Scene();

	void Render();
	void Update();

	void addObject(SceneObject*);
	void AddTriangleCollider(vec3 v1, vec3 v2, vec3 v3, vec3 uv1 = vec3(0, 0, 0), vec3 uv2 = vec3(0, 0, 0), vec3 uv3 = vec3(0, 0, 0), std::string textureName = "");

	vec3 boundaryMin;
	vec3 boundaryMax;

	bool showSphereColliders;

	Skydome* skydome;

private:
	struct Triangle
	{
		vec3 v1, v2, v3;
		vec3 uv1, uv2, uv3;
		std::string textureName;
		vec3 n;
		float A, B, C, D;
	};

	std::vector<SceneObject*> sceneObjects;
	std::vector<Triangle> collisionTriangles;
};
#endif // !SCENE_H
