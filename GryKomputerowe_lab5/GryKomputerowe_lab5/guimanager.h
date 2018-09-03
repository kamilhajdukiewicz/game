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
	void renderGame();
	void renderText(std::string text, int offsetTop, int offsetLeft=90);
};