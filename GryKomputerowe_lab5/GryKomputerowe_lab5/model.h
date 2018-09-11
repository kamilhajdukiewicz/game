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

	vec3 color;

	vec3 modelTranslation;
	vec3 modelScale;

	std::string textureName;

	bool hasNormals;
	bool hasTexCoords;

	GLuint displayListID;

	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<vec3> uvs;
};
#endif // !MODEL_H

