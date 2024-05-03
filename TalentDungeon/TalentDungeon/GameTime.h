#pragma once
#include <Windows.h>

namespace gameTime
{
#define DT GameTime::GetInstance()->GetDeltaTime()
#define OneSecond 1000
	class GameTime
	{
	private:
		static GameTime* instance;

		LARGE_INTEGER frequency;
		LARGE_INTEGER prevCounter;
		LARGE_INTEGER currentCounter;
		float deltaTime;
		float timeScale = 1.0f;

	public:

	private:
		GameTime();
		~GameTime();

	public:
		static GameTime* GetInstance();
		static void DestroyInstance();

		void InitTime();
		void UpdateTime();
		float GetDeltaTime();

		const float GetFrameRate();
		float GetTimeScale();
		void SetTimeScale(float n);
	};
}
