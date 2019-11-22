#pragma once
#include "Simplex/Simplex.h"
#include <time.h>
#include <ctime>

namespace Simplex {

	class GameManager
	{
		static GameManager* m_pInstance; //Singleton pointer

		//Indicates the height of the player
		int blockChunk;

		//The length of a chunk
		int m_iChunkHeight;

		//The number of random blocks when generating a new chunk of platforms
		int m_iRandomBlocks;

		//The number of random block around each path blocks
		int m_iRandomPathBlocks;

		//The average distance between each path blocks
		float m_fAvgGap;

		//Half width of the game field
		int halfWidth;

		//The next "Path" block's position
		vector3 m_v3PathBlockPosition;

	public:
		static GameManager* GetInstance();

		GameManager(void);

		GameManager(GameManager const& other);

		GameManager& operator=(GameManager const& other);

		void Init();

		//Get the path block positon
		vector3 GetPathBlockPotition(vector3 pos);

		//Set the path block position
		void SetPathBlockPosition(vector3 pos);

		//Automaticly set the next path block position
		void NextPathBlock();

		void GenerateRandomPositionAroundPathBlock();

		void GenerateRandomPositionInChunk();

	};

}

