#include "stdafx.h"
#include "guimanager.h"
#include "gamemanager.h"

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

void GUIManager::renderGameHUD()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 1200, 0.0, 1000);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	showScore();
	showTime();
	showFuel();
}

void GUIManager::showScore()
{
	renderText("Your Points: ", 0, 20);
}

void GUIManager::showTime()
{
	renderText("Time: ", 0, 550);
}

void GUIManager::showFuel()
{
	renderText("Fuel: ", 0, 1100);
}

void GUIManager::changeScreen(int state)
{
	if (state == 0)
	{
		startScreen();
	}
	else if(state==1)
	{
		endScreen();
	}
	else
	{
		renderGameHUD();
	}
};
