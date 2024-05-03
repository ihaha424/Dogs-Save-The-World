#pragma once

#include <Windows.h>

namespace game
{
	class GameManager
	{
	private:
		static GameManager* instance;

		int m_UpdateCount = 0;
		int m_FixedUpdateCount = 0;

	private:
		GameManager();
		~GameManager();

		void DrawFPS();
	public:
		static GameManager* GetInstance();
		static void DestroyInstance();


		void Initialize();
		void Update();
		void FixeUpdate();
		void Render();
		void Finalize();
		void Run();


	};
}