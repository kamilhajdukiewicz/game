#include "stdafx.h"
#include "gamemanager.h"
#include "guimanager.h"
#include "player.h"
#include "model.h"
#include "scene.h"
#include "building.h"
#include "texturemanager.h"

int state = 0;
GUIManager g_manager;
Scene scene;
Player *player;
void OnRender();
void OnReshape(int, int);
void OnKeyPress(unsigned char, int, int);
void OnKeyDown(unsigned char, int, int);
void OnKeyUp(unsigned char, int, int);
void OnTimer(int);
void OnMouseMove(int, int);
void OnMouseClick(int, int, int, int);

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

	player = new Player();
	scene.addObject(player);

	for (int i = 0; i < 30; i=i+5)
	{
		for (int j = 0; j < 30; j = j + 5)
		{
			scene.addObject(new Building(vec3(i, 0, j), vec3(1, 0, 0), 1.0f));
		}
	}
	
	scene.boundaryMin = vec3(-50, 1, -50);
	scene.boundaryMax = vec3(50, 10, 50);
	scene.AddTriangleCollider(vec3(100, 0, -100), vec3(-100, 0, -100), vec3(100, 0, 100), vec3(1, 1), vec3(0, 1), vec3(1, 0), "grass");
	scene.AddTriangleCollider(vec3(-100, 0, -100), vec3(-100, 0, 100), vec3(100, 0, 100), vec3(0, 1), vec3(0, 0), vec3(1, 0), "grass");

	//scene.AddTriangleCollider(vec3(-100, 20, 100), vec3(-100, 0, 100), vec3(-100, 20, -100), vec3(0, 1), vec3(0, 0), vec3(1, 1), "brick");
	//scene.AddTriangleCollider(vec3(-100, 0, 100), vec3(-100, 0, -100), vec3(-100, 20, -100), vec3(0, 0), vec3(1, 0), vec3(1, 1), "brick");
	//scene.AddTriangleCollider(vec3(100, 0, -100), vec3(100, 20, -100), vec3(-100, 20, -100), vec3(1, 0), vec3(1, 1), vec3(0, 1), "brick");
	//scene.AddTriangleCollider(vec3(-100, 20, -100), vec3(-100, 0, -100), vec3(100, 0, -100), vec3(0, 1), vec3(0, 0), vec3(1, 0), "brick");
	//scene.AddTriangleCollider(vec3(100, 20, -100), vec3(100, 0, -100), vec3(100, 20, 100), vec3(0, 1), vec3(0, 0), vec3(1, 1), "brick");
	//scene.AddTriangleCollider(vec3(100, 0, -100), vec3(100, 0, 100), vec3(100, 20, 100), vec3(0, 0), vec3(1, 0), vec3(1, 1), "brick");

	//scene.AddTriangleCollider(vec3(-52, 0, 45), vec3(-52, 22, 45), vec3(-30, 22, 45), vec3(1, 0), vec3(1, 1), vec3(0, 1), "brick");
	//scene.AddTriangleCollider(vec3(-30, 22, 45), vec3(-30, 0, 45), vec3(-52, 0, 45), vec3(0, 1), vec3(0, 0), vec3(1, 0), "brick");
	//scene.AddTriangleCollider(vec3(-52, 22, 45), vec3(-52, 0, 45), vec3(-52, 22, -45), vec3(0, 1), vec3(0, 0), vec3(1, 1), "brick");
	//scene.AddTriangleCollider(vec3(-52, 0, 45), vec3(-52, 0, -45), vec3(-52, 22, -45), vec3(0, 0), vec3(1, 0), vec3(1, 1), "brick");
	//scene.AddTriangleCollider(vec3(37, 0, -45), vec3(50, 22, -45), vec3(-52, 22, -45), vec3(1, 0), vec3(1, 1), vec3(0, 1), "brick");
	//scene.AddTriangleCollider(vec3(-52, 22, -45), vec3(-52, 0, -45), vec3(37, 0, -45), vec3(0, 1), vec3(0, 0), vec3(1, 0), "brick");
	//scene.AddTriangleCollider(vec3(37, 22, -45), vec3(37, 0, -45), vec3(37, 22, 37), vec3(0, 1), vec3(0, 0), vec3(1, 1), "brick");
	//scene.AddTriangleCollider(vec3(37, 0, -45), vec3(37, 0, 37), vec3(37, 22, 37), vec3(0, 0), vec3(1, 0), vec3(1, 1), "brick");
	//scene.AddTriangleCollider(vec3(37, 22, 37), vec3(37, 0, 37), vec3(30, 22, 30), vec3(0, 1), vec3(0, 0), vec3(1, 1), "brick");
	//scene.AddTriangleCollider(vec3(37, 0, 37), vec3(37, 0, 22), vec3(30, 22, 30), vec3(0, 0), vec3(1, 0), vec3(1, 1), "brick");

	TextureManager::getInstance()->LoadTexture("grass", "../Resources/Textures/grass.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("skydome", "../Resources/Textures/skydome.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);
	TextureManager::getInstance()->LoadTexture("brick", "../Resources/Textures/brick.jpg", GL_LINEAR, GL_LINEAR_MIPMAP_NEAREST);


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

}

void OnTimer(int id) {

	if (keystate['w']) {
		player->velocity_vertical = 1;
	}
	if (keystate['s']) {
		player->velocity_vertical = -1;
	}
	if (keystate['a']) {
		player->velocity_horizontal = 1;
	}
	if (keystate['d']) {
		player->velocity_horizontal = -1;
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

	glutTimerFunc(17, OnTimer, 0);
}

void OnRender() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float previousT = T;
	T = glutGet(GLUT_ELAPSED_TIME);

	gluLookAt(
		player->pos.x, player->pos.y, player->pos.z,
		player->pos.x + player->dir.x, player->pos.y + player->dir.y, player->pos.z + player->dir.z,
		0.0f, 1.0f, 0.0f
	);


	scene.Render();
	g_manager.changeScreen(state);


	GLfloat l0_ambient[] = { 0.2f, 0.2f, 0.2f };
	GLfloat l0_diffuse[] = { 1.0f, 1.0f, 1.0 };
	GLfloat l0_specular[] = { 0.5f, 0.5f, 0.5f };
	GLfloat l0_position[] = { player->pos.x, player->pos.y, player->pos.z, 1.0f };
	GLfloat l0_position2[] = { 15, 0, 3, 1.0f };

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_position);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0);
		
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