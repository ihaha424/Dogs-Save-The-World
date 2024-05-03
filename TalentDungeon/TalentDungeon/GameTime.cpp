#include "GameTime.h"
#include "cmath"

namespace gameTime
{
	GameTime* GameTime::instance = nullptr;
	GameTime::GameTime() {}
	GameTime::~GameTime() {}

	GameTime* GameTime::GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new GameTime();
		}
		return instance;
	}

	void GameTime::DestroyInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void GameTime::InitTime()
	{
		QueryPerformanceFrequency(&frequency);	// ���� Ÿ�̸Ӱ� 1�� ���� ������ų�� �ִ� TickCount ��
		QueryPerformanceCounter(&prevCounter);  // �ʱ� TickCount ��
	}

	void GameTime::UpdateTime()
	{
		QueryPerformanceCounter(&currentCounter); // ���� TickCount ��
		deltaTime = static_cast<float>(currentCounter.QuadPart - prevCounter.QuadPart) /
			static_cast<float>(frequency.QuadPart);  // ī�������̸� �ð� �ʴ����� ��ȯ

		prevCounter = currentCounter;
	}


	const float GameTime::GetFrameRate()
	{
		if (deltaTime == 0) return 0;

		return ceil(((1000.0f / deltaTime) * 1000) / 1000);
	}

	float GameTime::GetTimeScale()
	{
		return timeScale;
	}
	void GameTime::SetTimeScale(float n)
	{
		if (n < 0)
			return;
		timeScale = n;
	}
	float GameTime::GetDeltaTime()
	{
		return (deltaTime * timeScale);
	}
}