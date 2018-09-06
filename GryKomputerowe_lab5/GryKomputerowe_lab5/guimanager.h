#pragma once
#include "stdafx.h"
#include <iostream>

class GUIManager
{
public:
	void changeScreen(int);
	GUIManager();
	~GUIManager();
private:
	void startScreen();
	void endScreen();
	void renderGameHUD();
	void showScore();
	void showTime();
	void showFuel();
	void renderText(std::string text, int offsetTop, int offsetLeft=90);
};