#include "stdafx.h"
#include "scene.h"
#include "texturemanager.h"
#include "skydome.h"

Scene::Scene()
{
	skydome = new Skydome(150, "skydome");
}

Scene::~Scene()
{
	for (unsigned int i = 0; i < sceneObjects.size(); i++)
		delete sceneObjects[i];

	sceneObjects.clear();
}

void Scene::Render()
{
	for (unsigned int i = 0; i < sceneObjects.size(); i++)
		sceneObjects[i]->Render();

	if (showSphereColliders)
	{
		glDisable(GL_LIGHTING);

		glColor3f(1, 0, 0);
		for (unsigned int i = 0; i < sceneObjects.size(); i++)
		{
			glPushMatrix();
			glTranslatef(sceneObjects[i]->pos.x, sceneObjects[i]->pos.y, sceneObjects[i]->pos.z);
			glRotatef(90, 1, 0, 0);
			glutWireSphere(sceneObjects[i]->radius, 24, 24);
			glPopMatrix();
		}
		glEnable(GL_LIGHTING);
	}

	for (unsigned int i = 0; i < collisionTriangles.size(); i++)
	{
		if (!collisionTriangles[i].textureName.empty())
		{
			glEnable(GL_TEXTURE_2D);
			TextureManager::getInstance()->BindTexture(collisionTriangles[i].textureName);
		}

		float ambient[] = { 0.5f, 0.5f, 0.5f };
		float diffuse[] = { 1.0f, 1.0f, 1.0f };
		float specular[] = { 0.0f, 0.0f, 0.0f };

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glBegin(GL_TRIANGLES);
		glNormal3f(collisionTriangles[i].n.x, collisionTriangles[i].n.y, collisionTriangles[i].n.z);
		glTexCoord2f(collisionTriangles[i].uv1.x, collisionTriangles[i].uv1.y);
		glVertex3f(collisionTriangles[i].v1.x, collisionTriangles[i].v1.y, collisionTriangles[i].v1.z);
		glTexCoord2f(collisionTriangles[i].uv2.x, collisionTriangles[i].uv2.y);
		glVertex3f(collisionTriangles[i].v2.x, collisionTriangles[i].v2.y, collisionTriangles[i].v2.z);
		glTexCoord2f(collisionTriangles[i].uv3.x, collisionTriangles[i].uv3.y);
		glVertex3f(collisionTriangles[i].v3.x, collisionTriangles[i].v3.y, collisionTriangles[i].v3.z);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	}

	skydome->Render();
}

void Scene::Update()
{
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		SceneObject* obj = sceneObjects[i];

		obj->prevPos = obj->pos;

		obj->pos.y -= 0.3f;

		if ((obj->pos.x + obj->radius) > boundaryMax.x)
			obj->pos.x = boundaryMax.x - obj->radius;

		if ((obj->pos.y + obj->radius) > boundaryMax.y)
			obj->pos.y = boundaryMax.y - obj->radius;

		if ((obj->pos.z + obj->radius) > boundaryMax.z)
			obj->pos.z = boundaryMax.z - obj->radius;

		if ((obj->pos.x - obj->radius) < boundaryMin.x)
			obj->pos.x = boundaryMin.x + obj->radius;

		if ((obj->pos.y - obj->radius) < boundaryMin.y)
			obj->pos.y = boundaryMin.y + obj->radius;

		if ((obj->pos.z - obj->radius) < boundaryMin.z)
			obj->pos.z = boundaryMin.z + obj->radius;
	}

	for (int i = 0; i < sceneObjects.size(); i++)
	{
		for (int j = i + 1; j < sceneObjects.size(); j++)
		{
			SceneObject* obj1 = sceneObjects[i];
			SceneObject* obj2 = sceneObjects[j];

			float r = vec3::distance(obj1->pos, obj2->pos);

			float d = (obj1->radius + obj2->radius) - r;

			if (d > 0)
			{
				vec3 v1 = obj1->pos - obj2->pos;
				vec3 v2 = obj2->pos - obj1->pos;

				v1 = v1.normalized();
				v2 = v2.normalized();

				obj1->pos = obj1->pos + v1 * (d / 2) * 1.2f;
				obj2->pos = obj2->pos + v2 * (d / 2) * 1.2f;

				float total_force = obj1->force.length() + obj2->force.length();

				obj1->force = v1 * total_force * 0.5f;
				obj2->force = v2 * total_force * 0.5;
			}
		}
	}

	for (unsigned int i = 0; i < sceneObjects.size(); i++)
		sceneObjects[i]->Update();

	for (unsigned int i = 0; i < sceneObjects.size(); i++)
	{
		SceneObject* obj = sceneObjects[i];

		for (int j = 0; j < collisionTriangles.size(); j++)
		{
			Triangle tr = collisionTriangles[j];

			float currDist = tr.A * obj->pos.x + tr.B * obj->pos.y + tr.C * obj->pos.z + tr.D;
			float prevDist = tr.A * obj->prevPos.x + tr.B * obj->prevPos.y + tr.C * obj->prevPos.z + tr.D;

			if ((currDist * prevDist < 0) || abs(currDist) < obj->radius)
			{
				// Rzut pozycji obiektu na plaszczyzne
				vec3 p = obj->pos - tr.n * currDist;

				// Przesuniecie punktu do srodka trojkata o dlugosc promienia kolidera
				vec3 r = (tr.v1 + tr.v2 + tr.v3) * (1.0f / 3.0f) - p;
				r = r.normalized();
				p = p + r * obj->radius;

				// Obliczenie v, w, u - wspolrzednych barycentrycznych
				vec3 v0 = tr.v2 - tr.v1, v1 = tr.v3 - tr.v1, v2 = p - tr.v1;
				float d00 = vec3::dot(v0, v0);
				float d01 = vec3::dot(v0, v1);
				float d11 = vec3::dot(v1, v1);
				float d20 = vec3::dot(v2, v0);
				float d21 = vec3::dot(v2, v1);
				float denom = d00 * d11 - d01 * d01;

				float v = (d11 * d20 - d01 * d21) / denom;
				float w = (d00 * d21 - d01 * d20) / denom;
				float u = 1.0f - v - w;

				// Sprawdzenie czy punkt jest w srodku trojkata
				if (v >= 0 && w >= 0 && (v + w) <= 1)
				{
					float d = obj->radius - currDist;

					obj->pos = obj->pos + tr.n * d;

					obj->force = obj->force - tr.n * vec3::dot(tr.n, obj->force) * 2;
				}
			}
		}
	}

	for (std::vector<SceneObject*>::iterator it = sceneObjects.begin(); it != sceneObjects.end();)
	{
		if ((*it)->isAlive)
		{
			it++;
		}
		else
		{
			delete (*it);
			it = sceneObjects.erase(it);
		}
	}
	skydome->Update();
}

void Scene::addObject(SceneObject* object)
{
	sceneObjects.push_back(object);
}

void Scene::AddTriangleCollider(vec3 v1, vec3 v2, vec3 v3, vec3 uv1, vec3 uv2, vec3 uv3, std::string textureName)
{
	Triangle t;

	t.v1 = v1;
	t.v2 = v2;
	t.v3 = v3;

	t.uv1 = uv1;
	t.uv2 = uv2;
	t.uv3 = uv3;

	t.textureName = textureName;

	t.n = vec3::cross(v1 - v3, v2 - v1);
	t.n = t.n.normalized();

	t.A = t.n.x;
	t.B = t.n.y;
	t.C = t.n.z;
	t.D = -(t.A * v1.x + t.B * v1.y + t.C*v1.z);

	collisionTriangles.push_back(t);
}
