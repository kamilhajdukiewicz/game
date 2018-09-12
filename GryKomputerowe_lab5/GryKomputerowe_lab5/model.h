#pragma once
#ifndef MODEL_H
#define MODEL_H

#include "stdafx.h"
#include "vec3.h"
#include "sceneobject.h"

class Model: public SceneObject
{
public:
	Model(vec3 pos, vec3 color);
	~Model();

	bool load(std::string filepath);

	void Render();
	void Update();

	void rotate();

	vec3 color;

	vec3 modelTranslation;
	vec3 modelScale;

	std::string textureName;

	bool hasNormals;
	bool hasTexCoords;

	GLuint displayListID;

	vec3 dir;
	float speed;

	float velocity_vertical;
	float velocity_horizontal;

	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<vec3> uvs;
};
#endif // !MODEL_H

