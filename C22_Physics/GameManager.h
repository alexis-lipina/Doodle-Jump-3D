#pragma once
#include "Simplex/Simplex.h"
#include <time.h>
#include <ctime>
#include <cmath>

namespace Simplex {

	class GameManager
	{
		static GameManager* m_pInstance; //Singleton pointer

		//Indicates the height of the player
		int blockChunk;

		//The length of a chunk
		int m_iChunkHeight;



		//The average vertical distance between each path blocks
		float m_fAvgYGap;

		//The max horizontal distance between each path blocks
		float m_fMaxXGap;

		//Half width of the game field
		int halfWidth;

		//The next "Path" block's position
		vector3 m_v3PathBlockPosition;



	public:

		//The number of random blocks when generating a new chunk of platforms
		int m_iRandomBlocks;

		//The number of random block around each path blocks
		int m_iRandomPathBlocks;

		static GameManager* GetInstance();

		GameManager(void);

		GameManager(GameManager const& other);

		GameManager& operator=(GameManager const& other);

		void Init();

		//Get the path block positon
		vector3 GetPathBlockPosition();

		//Set the path block position
		void SetPathBlockPosition(vector3 pos);

		float GetYAvgGap();

		//Automaticly set the next path block position
		void NextPathBlock();

		//return a random position around path block
		vector3 GenerateRandomPositionAroundPathBlock();

		//retern a random position in the current chunk
		vector3 GenerateRandomPositionInChunk();

		//Increment chunk counter
		void NextChunk();

		//Random Number Generators
		float RandomFloat(float min, float max);

		//Absolute Value
		float Absolute(float f);
	};

}

