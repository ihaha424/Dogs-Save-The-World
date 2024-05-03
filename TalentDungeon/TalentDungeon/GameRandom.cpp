#include "GameRandom.h"

namespace game
{
	GameRandom* GameRandom::instance = nullptr;
	GameRandom::GameRandom() {}
	GameRandom::~GameRandom() {}

	GameRandom* GameRandom::GetIncetance()
	{
		if (instance == nullptr)
		{
			instance = new GameRandom();
		}
		return instance;
	}

	void GameRandom::DestroyInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void GameRandom::Srand(unsigned int seed)
	{
		this->_seed = seed;
	}

	unsigned int GameRandom::RandInt()
	{
		this->_seed = ((this->_seed * 1103515245 + 12345) >> 16) & RAND_MAX;
		return (this->_seed);
	}

	unsigned int GameRandom::RandInt(unsigned int percent)
	{
		this->_seed = ((this->_seed * 1103515245 + 12345) >> 16) & RAND_MAX;
		unsigned int tmp = (this->_seed) % percent;
		return tmp;
	}

	unsigned int GameRandom::RandPercent(const int _count, ...)
	{
		va_list	list;
		int		amount;
		int* percent;
		int		randValue;
		int		curValue;
		int		count;

		if (_count <= 0 || _count > MaxPerCentListSize)
			return -1;
		if (_count == 1)
			return 0;

		amount = 0;
		percent = new int[_count];
		va_start(list, _count);
		curValue = va_arg(list, size_t);
		if (curValue < 0)
			return -1;
		percent[0] = curValue;
		amount += curValue;
		for (count = 1; count < _count; count++)
		{
			curValue = va_arg(list, size_t);
			if (curValue < 0)
				return -1;
			percent[count] = curValue + percent[count - 1];
			amount += curValue;
		}
		va_end(list);

		if (_count != count)
		{
			delete[] percent;
			return -1;
		}

		randValue = RandInt(amount);
		for (int i = 0; i < _count; i++)
		{
			if (randValue < percent[i])
			{
				delete[] percent;
				return i;
			}
		}
	}

	unsigned int GameRandom::RandPercent(const int _count, const unsigned int PercentList[])
	{
		int		amount;
		int* percent;
		int		randValue;
		int		curValue;
		int		count;

		if (_count <= 0 || _count > MaxPerCentListSize)
			return -1;
		if (_count == 1)
			return 0;

		amount = 0;
		percent = new int[_count];
		curValue = PercentList[0];
		percent[0] = curValue;
		amount += curValue;
		for (count = 1; count < _count; count++)
		{
			curValue = PercentList[count];
			percent[count] = curValue + percent[count - 1];
			amount += curValue;
		}

		if (_count != count)
		{
			delete[] percent;
			return -1;
		}

		randValue = RandInt(amount);
		for (int i = 0; i < _count; i++)
		{
			if (randValue < percent[i])
			{
				delete[] percent;
				return i;
			}
		}
	}

}
