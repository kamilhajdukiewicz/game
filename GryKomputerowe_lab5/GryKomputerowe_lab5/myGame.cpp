#include "stdafx.h"
#include "gamemanager.h"
#include "guimanager.h"
#include "player.h"
#include "model.h"
#include "scene.h"
#include "building.h"
#include "texturemanager.h"
#include "point.h"
#include "model.h"

int state = 0;
GUIManager g_manager;
Scene scene;
Player *player;
Model* model;
void OnRender();
void OnReshape(int, int);
void OnKeyPress(unsigned char, int, int);
void OnKeyDown(unsigned char, int, int);
void OnKeyUp(unsigned char, int, int);
void OnTimer(int);
void OnMouseMove(int, int);
void OnMouseClick(int, int, int, int);

bool fly=false;
vec3 mousePosition;

float T = 0;

bool captureMouse;

float windowResolutionX = 1200;
float windowResolutionY = 1000;
float windowCenterX = windowResolutionX / 2;
float windowCenterY = windowResolutionY / 2;

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(windowResolutionX, windowResolutionY);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("MyGame");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutTimerFunc(17, OnTimer, 0);
	glutPassiveMotionFunc(OnMouseMove);
	glutMotionFunc(OnMouseMove);
	glutMouseFunc(OnMouseClick);

	glEnable(GL_DEPTH_TEST);

	float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	glutSetCursor(GLUT_CURSOR_NONE);
	captureMouse = true;
	glutWarpPointer(windowCenterX, windowCenterY);

	player = Player::getInstance();
	scene.addObject(player);

	model = new Model(vec3(player->pos.x, 0, player->pos.z-4), vec3(0, 0.5f, 1));
	model->load("../Resources/Models/car2obj.obj");
	//model->textureName = "brick";
	model->modelTranslation = vec3(0, -0.8f, 0);
	model->modelScale = vec3(0.5, 0.5, 0.5);
	model->radius *= 0.5f;
	scene.addObject(model);

	for (int i = - 35; i < 30; i=i+5)
	{
		for (int j = -35; j < 30; j = j + 5)
		{
			scene.addObject(new Building(vec3(i, 0, j), vec3(1, 0, 0), 1.0f));
		}
	}

	for (float i = -32.5; i < 27.5; i = i + 5)
	{
		for (float j = -32.5; j < 27.5; j = j + 5)
		{
			scene.addPoint(new Point(vec3(i, 0, j), vec3(0, 1, 0), 0.5f, 2));
		}
	}
	//Point * point = new Point(vec3(-27.5f, 0, -27.5f), vec3(0, 1, 0), 0.5f, 2);
	//point->ambient = vec3(0.7f, 0.7f, 0.7f);
	//scene.addPoint(point);
	
	scene.boundaryMin = vec3(-50, 1, -50);
	scene.boundaryMax = vec3(50, 10, 50);
	scene.AddTriangleCollider(vec3(100, 0, -100), vec3(-100, 0, -100), vec3(100, 0, 100), vec3(1, 1), vec3(0, 1), vec3(1, 0), "bawtext");
	scene.AddTriangleCollider(vec3(-100, 0, -100), vec3(-100, 0, 100), vec3(100, 0, 100), vec3(0, 1), vec3(0, 0), vec3(1, 0), "bawtext");

	TextureManager::getInstance()->LoadTexture("grass", "../Resources/Textures/grass.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("skydome3", "../Resources/Textures/skydome3.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("bawtext", "../Resources/Textures/bawtext.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);


	glutMainLoop();

	return 0;
}

bool keystate[256];

void OnKeyPress(unsigned char key, int x, int y) {
	if (!keystate[key]) {
		OnKeyDown(key, x, y);
	}
	keystate[key] = true;
}

void OnKeyDown(unsigned char key, int x, int y) {

	if (key == 32) 
	{
		state = 2;
	}

	if (key == 27)
	{
		glutLeaveMainLoop();
	}


}

void OnKeyUp(unsigned char key, int x, int y) {
	keystate[key] = false;
}

void OnMouseMove(int x, int y)
{
	mousePosition.x = x;
	mousePosition.y = y;
}

void OnMouseClick(int button, int state, int x, int y)
{
	if (!fly)
		fly = true;
	else
		fly = false;
}

void OnTimer(int id) {

	if (state == 2)
	{

		if (keystate['w']) {
			model->velocity_vertical = 1;
			player->velocity_vertical = 1;
			model->rotateLeft = false;
			model->rotateRight = false;
			model->rotateForward = false;
		}
		if (keystate['s']) {
			model->velocity_vertical = -1;
			player->velocity_vertical = -1;
			model->rotateLeft = false;
			model->rotateRight = false;
			model->rotateForward = true;
		}
		if (keystate['a']) {
			model->velocity_horizontal = 1;
			player->velocity_horizontal = 1;
			model->rotateLeft = true;
			model->rotateRight = false;
			model->rotateForward = false;
		}
		if (keystate['d']) {
			model->velocity_horizontal = -1;
			player->velocity_horizontal = -1;
			model->rotateRight = true;
			model->rotateLeft = false;
			model->rotateForward = false;
		}
		if (keystate['q']) {

		}

		if (captureMouse)
		{
			float theta = atan2(player->dir.z, player->dir.x);
			float phi = asin(player->dir.y);

			theta += (round(mousePosition.x) - windowCenterX) * 0.01;
			phi -= (round(mousePosition.y) - windowCenterY) * 0.01;

			if (phi > 1.4) phi = 1.4;
			if (phi < -1.4) phi = -1.4;

			player->dir.x = cos(theta) * cos(phi);
			player->dir.y = sin(phi);
			player->dir.z = sin(theta) * cos(phi);

			glutWarpPointer(windowCenterX, windowCenterY);
		}
		scene.Update();
	}

	glutTimerFunc(17, OnTimer, 0);
}

void OnRender() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float previousT = T;
	T = glutGet(GLUT_ELAPSED_TIME);

	if (!fly)
	{
		gluLookAt(
			model->pos.x, model->pos.y + 2, model->pos.z + 3,
			model->pos.x, model->pos.y, model->pos.z,
			0.0f, 1.0f, 0.0f
		);
	}
	else
	{
		gluLookAt(
			0, player->pos.y+10, 0,
			model->pos.x, model->pos.y, model->pos.z,
			0.0f, 1.0f, 0.0f
		);
	}

	g_manager.changeScreen(state,player->score,player->fuel,player->hp);

	if (player->fuel <= 0 || player->hp <=0)
	{
		state = 3;
	}

	scene.Render();

	GLfloat l0_ambient[] = { 0.2f, 0.2f, 0.2f };
	GLfloat l0_diffuse[] = { 1.0f, 1.0f, 1.0 };
	GLfloat l0_specular[] = { 0.5f, 0.5f, 0.5f };
	GLfloat l0_position[] = { model->pos.x, model->pos.y, model->pos.z-0.5, 1.0f };
	GLfloat l0_position2[] = { model->pos.x, model->pos.y, model->pos.z+3, 0.5f };

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_position);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0);

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, l0_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l0_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l0_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, l0_position2);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.2);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0);
		
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void OnReshape(int width, int height) {

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glViewport(0, 0, width, height);

	gluPerspective(60.0f, (float)width / height, .01f, 120.0f);

}