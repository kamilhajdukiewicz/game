#include "stdafx.h"
#include "guimanager.h"
#include "gamemanager.h"
#include <string>

GUIManager::GUIManager()
{
}

GUIManager::~GUIManager()
{
}

void GUIManager::startScreen()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 1200, 0.0, 1000);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	renderText("Bus simulator", 200);
	renderText("Celem gry jest zdobycie jak najwiekszej iloœci punktow w ci¹gu 1 min", 220);
	renderText("Punkty zdobywa sie zbierjac pasazerow", 240);
	renderText("Trzeba jednak uwazac na pijakow, gdyz kazdy pijak powoduje, ze wsyscy pasazerowie wysiadaja i tracimy nasze punkty", 260);
	renderText("Sterowanie:", 320);
	renderText("w, s - jedz do przodu i do ty³u", 340);
	renderText("a, d - skrec w lewo i w prawo", 360);

	renderText("Aby rozpoczac gre wcisnij Spacje!", 420);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void GUIManager::endScreen()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 1200, 0.0, 1000);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	renderText("You lose", 200, 550);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void GUIManager::winScreen(int score)
{

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 1200, 0.0, 1000);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	renderText("THE END", 150, 560);
	renderText("Your Score: "+std::to_string(score), 200, 550);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void GUIManager::renderText(std::string text, int offsetTop, int offsetLeft)
{
	glColor3f(0.0, 1.0, 0.0);
	glRasterPos2i(offsetLeft, 1000 - offsetTop - 50);

	void * font = GLUT_BITMAP_9_BY_15;
	for (std::string::iterator i = text.begin(); i != text.end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}

}

void GUIManager::renderGameHUD(int score, float fuel, int hp)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 1200, 0.0, 1000);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	showScore(score);
	showHp(hp);
	showFuel(fuel);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void GUIManager::showScore(int score)
{
	renderText("Your Points: "+std::to_string(score), 0, 550);
}

void GUIManager::showHp(int hp)
{
	renderText("Hp: "+std::to_string(hp), 0, 20);
}

void GUIManager::showFuel(float fuel)
{
	renderText("Fuel: "+std::to_string(fuel), 0, 1100);
}

void GUIManager::changeScreen(int state, int score, float fuel, int hp)
{
	if (state == 0)
	{
		startScreen();
	}
	else if(state==1)
	{
		endScreen();
	}
	else if(state==2)
	{
		renderGameHUD(score, fuel, hp);
	}
	else if (state == 3)
	{
		winScreen(score);
	}
};
