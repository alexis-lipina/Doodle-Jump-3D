#pragma once
#include "Simplex/Simplex.h"
#include <time.h>

namespace Simplex {

	class GameManager
	{
		static GameManager* m_pInstance; //Singleton pointer

		//Indicates the height of the player
		int blockChunk;

		//The number of random blocks when generating a new chunk of platforms
		int randomBlocks;

		//The next "Path" block's position
		vector3 pathBlockPosition;

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

	};

}

