#include "stdafx.h"
#include "gamemanager.h"

GameManager* GameManager::instance = NULL;

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

GameManager* GameManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new GameManager();
	}
	return instance;
}
