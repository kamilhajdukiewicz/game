#pragma once
#include "stdafx.h"
#include <iostream>

class GUIManager
{
public:
	void changeScreen(int, int score=0, float fuel=0, int hp=100);
	GUIManager();
	~GUIManager();
private:
	void startScreen();
	void endScreen();
	void renderGameHUD(int,float,int);
	void showScore(int score);
	void showHp(int);
	void showFuel(float fuel);
	void winScreen(int);
	void renderText(std::string text, int offsetTop, int offsetLeft=90);
};