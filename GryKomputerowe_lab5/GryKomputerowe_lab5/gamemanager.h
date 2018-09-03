#pragma once
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "guimanager.h"

class GameManager
{
public:
	static GameManager* getInstance();
private:
	static GameManager* instance;
	GameManager();
	~GameManager();
	GUIManager g_manager;
};

#endif // !GAME_MANAGER_H