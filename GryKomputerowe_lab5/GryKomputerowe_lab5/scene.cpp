#include "stdafx.h"
#include "scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{
	for (unsigned int i = 0; i < sceneObjects.size(); i++)
		delete sceneObjects[i];

	sceneObjects.clear();
}

void Scene::addObject(SceneObject* object)
{
	sceneObjects.push_back(object);
}
