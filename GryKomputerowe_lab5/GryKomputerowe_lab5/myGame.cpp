#include "stdafx.h"
#include "gamemanager.h"
#include "guimanager.h"
#include "player.h"
#include "model.h"
#include "scene.h"
#include "building.h"

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

	//glClearColor(0.74902f, 0.847059f, 0.847059f, 1.0);

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutTimerFunc(17, OnTimer, 0);
	glutPassiveMotionFunc(OnMouseMove);
	glutMotionFunc(OnMouseMove);
	glutMouseFunc(OnMouseClick);

	glEnable(GL_DEPTH_TEST);

	//float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

	//glEnable(GL_LIGHTING);
	//glShadeModel(GL_SMOOTH);

	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);

	glutSetCursor(GLUT_CURSOR_NONE);
	captureMouse = true;
	glutWarpPointer(windowCenterX, windowCenterY);

	player = new Player();
	scene.addObject(player);

	scene.addObject(new Building(vec3(0, 0, 0), vec3(1, 0, 0),2.0f));



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
	
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void OnReshape(int width, int height) {

	// Wybor macierzy - macierz Projekcji.
	glMatrixMode(GL_PROJECTION);

	// Zaladowanie macierzy jednostkowej.
	glLoadIdentity();

	// Okreslenie obszaru renderowania - caly obszar okna.
	glViewport(0, 0, width, height);

	// Chcemy uzyc kamery perspektywicznej o kacie widzenia 60 stopni
	// i zasiegu renderowania 0.01-100.0 jednostek.
	gluPerspective(60.0f, (float)width / height, .01f, 100.0f);

}