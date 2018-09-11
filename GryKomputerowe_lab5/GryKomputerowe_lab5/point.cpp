#include "stdafx.h"
#include "point.h"

Point::Point(vec3 pos, vec3 color, float radius, float weight)
{
	this->pos = pos;
	this->diffuse = color;
	this->radius = radius;
	this->weight = weight;

	radiusChangePerUpdate = 0;
}

Point::~Point(void)
{

}

void Point::Render()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, &ambient.x);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &diffuse.x);
	glMaterialfv(GL_FRONT, GL_SPECULAR, &specular.x);

	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glutSolidSphere(radius, 24, 24);
	glPopMatrix();
}

void Point::Update()
{
	pos.x += force.x / weight;
	pos.y += force.y / weight;
	pos.z += force.z / weight;

	force.x /= 1.2;
	force.y /= 1.2;
	force.z /= 1.2;

	radius += radiusChangePerUpdate;

	if (radius <= 0)
	{
		isAlive = false;
	}
}
