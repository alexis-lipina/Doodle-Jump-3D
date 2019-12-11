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
	m_iChunkHeight = 200;

	m_iRandomBlocks = 30;
	m_iRandomPathBlocks = 1;

	halfWidth = 19.0f;

	m_fAvgYGap = 3.5f;

	m_fMaxXGap = 6.0f;

	m_v3PathBlockPosition = vector3(0, 3, 0);


}

vector3 Simplex::GameManager::GetPathBlockPosition(){return m_v3PathBlockPosition;}

void Simplex::GameManager::SetPathBlockPosition(vector3 pos){m_v3PathBlockPosition = pos;}

float Simplex::GameManager::GetYAvgGap()
{
	return m_fAvgYGap;
}

void Simplex::GameManager::NextPathBlock()
{
	float gap = RandomFloat(-m_fMaxXGap, m_fMaxXGap);

	while (Absolute(gap) < 1.0f) {
		gap = RandomFloat(-m_fMaxXGap, m_fMaxXGap);
	}
	float xPos = m_v3PathBlockPosition.x + gap;
	float yPos = m_v3PathBlockPosition.y + m_fAvgYGap + RandomFloat(-1.0,1.0);

	//Make sure xPos is in-bound
	if (Absolute(xPos) >= halfWidth) {

		if (xPos < 0) {
			xPos = 19 - RandomFloat(1.0f,3.0f);
		}

		else if (xPos > 0) {
			xPos = -19 + RandomFloat(1.0f, 3.0f);
		}
	}

	m_v3PathBlockPosition = vector3(xPos, yPos, 0);
}

vector3 Simplex::GameManager::GenerateRandomPositionAroundPathBlock()
{
	float xPos = m_v3PathBlockPosition.x + RandomFloat(-10.0,10.0);

	//Make sure xPos is in-bound
	if (Absolute(xPos) >= halfWidth) {

		if (xPos < 0) {
			xPos = 19 - RandomFloat(1.0f, 3.0f);
		}

		else if (xPos > 0) {
			xPos = -19 + RandomFloat(1.0f, 3.0f);
		}
	}

	float yPos = m_v3PathBlockPosition.y + RandomFloat(-8.0, 8.0);

	if (yPos < 4.0) {
		yPos = 4.0;
	}

	return vector3(xPos, yPos, 0.0);
}

vector3 Simplex::GameManager::GenerateRandomPositionInChunk()
{
	float xPos = RandomFloat(-20.0, 20.0);
	float yPos = RandomFloat(4.0 + (((float)blockChunk - 1.0f) * (float)m_iChunkHeight), blockChunk * m_iChunkHeight);

	return vector3(xPos, yPos, 0);
}

int Simplex::GameManager::GetChunk()
{
	return blockChunk;
}

void Simplex::GameManager::NextChunk()
{
	blockChunk++;
}

float Simplex::GameManager::RandomFloat(float min, float max)
{
	return (min)+static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - (min))));
}

float Simplex::GameManager::Absolute(float f)
{
	if (f == 0)
		return f;

	if (f < 0)
		f = -f;

	return f;
}
