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

	blockChunk = 1;
	m_iChunkHeight = 100;

	m_iRandomBlocks = 10;
	m_iRandomPathBlocks = 5;

	halfWidth = 20;

	m_v3PathBlockPosition = vector3(RandomFloat(-5.0,5.0), m_fAvgYGap + RandomFloat(), 0);

	m_fAvgYGap = 3.0f;
}

vector3 Simplex::GameManager::GetPathBlockPotition(vector3 pos){return m_v3PathBlockPosition;}

void Simplex::GameManager::SetPathBlockPosition(vector3 pos){m_v3PathBlockPosition = pos;}

void Simplex::GameManager::NextPathBlock()
{
	float xPos = m_v3PathBlockPosition.x + RandomFloat(-5.0, 5.0);
	float yPos = m_v3PathBlockPosition.y + m_fAvgYGap + RandomFloat();

	//Make sure xPos is in-bound
	if (abs(xPos) > halfWidth) {

		if (xPos < 0) {
			xPos = halfWidth - (halfWidth - xPos);
		}

		if (xPos > 0) {
			xPos = -halfWidth + (xPos - halfWidth);
		}
	}

	m_v3PathBlockPosition = vector3(xPos, yPos, 0);
	
}

vector3 Simplex::GameManager::GenerateRandomPositionAroundPathBlock()
{
	float xPos = m_v3PathBlockPosition.x + RandomFloat(-5.0,5.0);
	if (abs(xPos) > halfWidth) {

		if (xPos < 0) {
			xPos = halfWidth - (halfWidth - xPos);
		}

		if (xPos > 0) {
			xPos = -halfWidth + (xPos - halfWidth);
		}
	}

	float yPos = m_v3PathBlockPosition.x + RandomFloat(-5.0, 5.0);

	if (yPos < 5.0) {
		yPos = 5.0;
	}

	return vector3(xPos, yPos, 0.0);

}

vector3 Simplex::GameManager::GenerateRandomPositionInChunk()
{
	float xPos = RandomFloat(-20.0, 20.0);
	float yPos = RandomFloat(6.0 + (((float)blockChunk - 1) * 100.0), blockChunk * 100);

	return vector3(xPos, yPos, 0);
}

void Simplex::GameManager::NextChunk()
{
	blockChunk++;
}

float Simplex::GameManager::RandomFloat()
{
	return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}

float Simplex::GameManager::RandomFloat(float min, float max)
{
	return (min)+static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - (min))));
}
