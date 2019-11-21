#include "GameManager.h"
using namespace Simplex;

Simplex::GameManager* Simplex::GameManager::m_pInstance = nullptr;

GameManager* GameManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new GameManager();
	}
	return m_pInstance;
}

// BIG 3
Simplex::GameManager::GameManager(void){Init();}
Simplex::GameManager::GameManager(GameManager const& other){}
GameManager& Simplex::GameManager::operator=(GameManager const& other){return *this;}

void Simplex::GameManager::Init()
{
	blockChunk = 0;
	randomBlocks = 10;
	pathBlockPosition = vector3(0, 5, 0);
}

vector3 Simplex::GameManager::GetPathBlockPotition(vector3 pos)
{
	return pathBlockPosition;
}

void Simplex::GameManager::SetPathBlockPosition(vector3 pos)
{
	pathBlockPosition = pos;
}

void Simplex::GameManager::NextPathBlock()
{
}
