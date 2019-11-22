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
	srand((unsigned)time(0));


	blockChunk = 0;
	m_iChunkHeight = 100;

	m_iRandomBlocks = 10;
	m_iRandomPathBlocks = 5;

	m_v3PathBlockPosition = vector3((rand() % 40) - 20, m_fAvgGap + (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)), 0);

	m_fAvgGap = 3.0f;

	halfWidth = 20;
}

vector3 Simplex::GameManager::GetPathBlockPotition(vector3 pos){return m_v3PathBlockPosition;}

void Simplex::GameManager::SetPathBlockPosition(vector3 pos){m_v3PathBlockPosition = pos;}

void Simplex::GameManager::NextPathBlock()
{
}

void Simplex::GameManager::GenerateRandomPositionAroundPathBlock()
{
}

void Simplex::GameManager::GenerateRandomPositionInChunk()
{
}
