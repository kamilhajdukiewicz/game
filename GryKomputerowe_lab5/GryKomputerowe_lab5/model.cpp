#include "stdafx.h"
#include "model.h"
#include "texturemanager.h"


Model::Model(vec3 pos, vec3 color)
{
	this->pos = pos;
	this->color = color;

	dir.x = 0.0f;
	dir.y = 0.0f;
	dir.z = -1.0f;

	speed = 0.3f;
	radius = 0.5f;

	velocity_horizontal = 0;
	velocity_vertical = 0;

	weight = 2;

	modelScale = vec3(1, 1, 1);

	hasNormals = false;
	hasTexCoords = false;

	displayListID = -1;

	rotateLeft = false;
	rotateRight = false;
}

Model::~Model()
{
	glDeleteLists(displayListID, 1);
}

bool Model::load(std::string filename)
{
	struct SFace {
		int v[3];
		int n[3];
		int uv[3];
	};

	FILE * fp = fopen(filename.c_str(), "r");

	if (fp == NULL) {
		printf("Nie wczytano pliku %s\n", filename.c_str());
		return false;
	}

	vertices.clear();

	std::vector<vec3> loaded_vertices;
	std::vector<vec3> loaded_normals;
	std::vector<vec3> loaded_uvs;
	std::vector<SFace> loaded_faces;

	char buf[256];

	while (fgets(buf, 256, fp)) {
		if (buf[0] == 'v' && buf[1] == ' ') {
			vec3 vertex;
			sscanf(buf, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			loaded_vertices.push_back(vertex);
		}
		if (buf[0] == 'v' && buf[1] == 'n') {
			vec3 normal;
			sscanf(buf, "vn %f %f %f", &normal.x, &normal.y, &normal.z);
			loaded_normals.push_back(normal);
			hasNormals = true;
		}
		if (buf[0] == 'v' && buf[1] == 't') {
			vec3 vertex;
			sscanf(buf, "vt %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			loaded_uvs.push_back(vertex);
			hasTexCoords = true;
		}
		if (buf[0] == 'f' && buf[1] == ' ') {
			if (!hasNormals && !hasTexCoords)
			{
				SFace face;
				sscanf(buf, "f %d %d %d",
					&face.v[0],
					&face.v[1],
					&face.v[2]);
				loaded_faces.push_back(face);
			}
			if (hasNormals && !hasTexCoords)
			{
				SFace face;
				sscanf(buf, "f %d//%d %d//%d %d//%d",
					&face.v[0], &face.n[0],
					&face.v[1], &face.n[1],
					&face.v[2], &face.n[2]);
				loaded_faces.push_back(face);
			}
			else if (hasNormals && hasTexCoords)
			{
				SFace face;
				sscanf(buf, "f %d/%d/%d %d/%d/%d %d/%d/%d",
					&face.v[0], &face.uv[0], &face.n[0],
					&face.v[1], &face.uv[1], &face.n[1],
					&face.v[2], &face.uv[2], &face.n[2]);
				loaded_faces.push_back(face);
			}
		}
	}

	fclose(fp);

	vec3 minVertex = loaded_vertices[0];
	vec3 maxVertex = loaded_vertices[1];

	for (int i = 0; i < loaded_faces.size(); ++i) {
		for (int j = 0; j < 3; ++j) {

			int idxV = loaded_faces[i].v[j] - 1;
			vertices.push_back(loaded_vertices[idxV]);

			if (hasNormals)
			{
				int idxN = loaded_faces[i].n[j] - 1;
				normals.push_back(loaded_normals[idxN]);
			}

			if (hasTexCoords)
			{
				int idxUV = loaded_faces[i].uv[j] - 1;
				uvs.push_back(loaded_uvs[idxUV]);
			}

			if (loaded_vertices[idxV].x < minVertex.x)
				minVertex.x = loaded_vertices[idxV].x;

			if (loaded_vertices[idxV].x > maxVertex.x)
				maxVertex.x = loaded_vertices[idxV].x;


			if (loaded_vertices[idxV].y < minVertex.y)
				minVertex.y = loaded_vertices[idxV].y;

			if (loaded_vertices[idxV].y > maxVertex.y)
				maxVertex.y = loaded_vertices[idxV].y;


			if (loaded_vertices[idxV].z < minVertex.z)
				minVertex.z = loaded_vertices[idxV].z;

			if (loaded_vertices[idxV].z > maxVertex.z)
				maxVertex.z = loaded_vertices[idxV].z;

		}
	}

	float diffX = maxVertex.x - minVertex.x;
	float diffY = maxVertex.y - minVertex.y;
	float diffZ = maxVertex.z - minVertex.z;

	if (diffX < diffY)
	{
		if (diffY < diffZ)
		{
			radius = diffZ;
		}
		else
		{
			radius = diffY;
		}
	}
	else
	{
		if (diffX < diffZ)
		{
			radius = diffZ;
		}
		else
		{
			radius = diffX;
		}
	}

	radius /= 2;
	weight = radius;

	displayListID = glGenLists(1);

	glNewList(displayListID, GL_COMPILE);

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < vertices.size(); i++)
	{
		if (hasNormals)glNormal3f(normals[i].x, normals[i].y, normals[i].z);
		if (hasTexCoords)glTexCoord2f(uvs[i].x, uvs[i].y);
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}

	glEnd();

	glEndList();

	return true;
}

void Model::Render()
{
	if (!textureName.empty())
	{
		glEnable(GL_TEXTURE_2D);
		TextureManager::getInstance()->BindTexture(textureName);
	}

	float mat_ambient[] = { 0.0f, 0.0f, 0.0f };
	float mat_diffuse[] = { color.x, color.y, color.z };
	float mat_specular[] = { 0.1f, 0.1f, 0.1f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	glPushMatrix();

	glTranslatef(pos.x, pos.y, pos.z);
	glTranslatef(modelTranslation.x, modelTranslation.y, modelTranslation.z);
	glScalef(modelScale.x, modelScale.y, modelScale.z);

	if (rotateLeft == true || rotateRight==true)
	{
		rotate();
	}

	glCallList(displayListID);

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}
void Model::rotate()
{
	if (rotateLeft == true)
	{
		glRotatef(-90, 0, 1, 0);
		//rotateRight = false;
	}
	if (rotateRight == true)
	{
		glRotatef(90, 0, 1, 0);
		//rotateLeft = false;
	}

}
void Model::Update()
{
	pos.x += dir.x * speed * velocity_vertical;
	pos.z += dir.z * speed * velocity_vertical;

	pos.x += dir.z * speed * velocity_horizontal;
	pos.z -= dir.x * speed * velocity_horizontal;

	velocity_vertical /= 1.2;
	velocity_horizontal /= 1.2;

	pos.x += force.x / weight;
	//pos.y += force.y / weight;
	pos.z += force.z / weight;

	force.x /= 1.2;
	//force.y /= 1.2;
	force.z /= 1.2;
}


