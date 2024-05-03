#pragma once

#include <cstdarg>


namespace game
{
#define RAND_MAX 0x7fff
#define MaxPerCentListSize 100

	class GameRandom
	{
	private:
		static GameRandom* instance;
		unsigned int _seed = 0;
	public:

	private:
		GameRandom();
		~GameRandom();
	public:
		static GameRandom* GetIncetance();
		static void DestroyInstance();

		void Srand(unsigned int seed);
		unsigned int RandInt();
		unsigned int RandInt(unsigned int percent);
		unsigned int RandPercent(const int _count, ...);
		unsigned int RandPercent(const int _count, const unsigned int PercentList[]);
	};
}