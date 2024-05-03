#include "GameManager.h"
#include "GameTime.h"
#include "GameRender.h"
#include "GameRandom.h"
#include "InputSystem.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "PathManager.h"
#include "ColliderManager.h"
#include "SharedData.h"
#include "Monster.h"
#include <iostream>
#include <string>

namespace game
{
	GameManager* GameManager::instance = nullptr;
	GameManager::GameManager() {}
	GameManager::~GameManager() {}

	GameManager* GameManager::GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new GameManager();
		}
		return instance;
	}

	void GameManager::DestroyInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void GameManager::Initialize()
	{
		input::InputSystem::GetInstance()->InitInput();
		PathManager::GetInstance()->InitPathManager();
		ResourceManager::GetInstance()->Initialize();
		SceneManager::GetInstance()->InitSceneManager();
		GameRender::GetInstance()->InitRender();
		gameTime::GameTime::GetInstance()->InitTime();
		ColliderManager::GetInstance()->Initialize();
	}


	void GameManager::Update()
	{
		static int LimitTime;

		++m_UpdateCount;
		//input::UpdateMouse();

		input::InputSystem::GetInstance()->Update();
		SceneManager::GetInstance()->Update();

		//	조작같은 것이 아니라 엔진차원에서 당연하게 진행되어야 하는 것들
		//	ex> 충돌체가 오브젝트를 따라 가는 것.
		ColliderManager::GetInstance()->FinalUpdate();
		//충돌처리
		ColliderManager::GetInstance()->Update();
		//Destroy object's collider
		ColliderManager::GetInstance()->DestoryUpdate();
		//Destroy Object
		SceneManager::GetInstance()->DestoryUpdate();
	}

	void GameManager::FixeUpdate()
	{
		static float elapsedTime;

		elapsedTime += gameTime::GameTime::GetInstance()->GetDeltaTime();

		while (elapsedTime >= FixedUpdateTime) //0.02초
		{
			++m_FixedUpdateCount;
			elapsedTime -= FixedUpdateTime;
			SceneManager::GetInstance()->FixedUpdate();
		}
	}

	void GameManager::Render()
	{
		game::GameRender::GetInstance()->BeginDraw();
		SceneManager::GetInstance()->Render(game::GameRender::GetInstance()->GetHDC());
		DrawFPS();
		game::GameRender::GetInstance()->EndDraw();
	}

	void GameManager::Finalize()
	{

		input::InputSystem::GetInstance()->DestroyInstance();
		PathManager::GetInstance()->DestoryPathManager();
		SceneManager::GetInstance()->DestroyInstance();
		GameRender::GetInstance()->DestroyInstance();
		gameTime::GameTime::GetInstance()->DestroyInstance();
		ColliderManager::GetInstance()->DestroyInstance();
		GameRandom::GetIncetance()->DestroyInstance();
		SharedData::GetInstance()->DestroyInstance();
		ResourceManager::GetInstance()->DestroyResourceManager();
	}

	void GameManager::Run()
	{
		MSG msg;

		while (true)
		{
			//GetMessage는 큐에 메시지가 있을 떄 까지 대기			//블러킹
			//PeekMessage는 메시지가 있으면 처리하고 아니면 넘어감 //넌블러킹
 			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{
					Monster::SetGameOverFlag(true);
					break;
				}

				if (msg.message == WM_KEYDOWN)
				{
					/*input::KeyDown(msg.wParam);*/
				}
				else if (msg.message == WM_KEYUP)
				{
					/*input::KeyUp(msg.wParam);*/
				}

				else
				{
					//GetMessage로 보내는 것 Proc로 처리하겠금 보내는 것.
					DispatchMessage(&msg);
				}
			}
			else
			{
				if (DebugModeFlag)
				{
					if (input::KEYHOLD(input::KEY::J))
					{
						gameTime::GameTime::GetInstance()->SetTimeScale(0.0f);
					}
					if (input::KEYHOLD(input::KEY::K))
					{
						gameTime::GameTime::GetInstance()->SetTimeScale(1.0f);
					}
				}
				gameTime::GameTime::GetInstance()->UpdateTime();

				FixeUpdate();

				Update();

				Render();
			}
		}

	}

	void GameManager::DrawFPS()
	{
		static float elapsedTime;
		static int FPS;
		static int ShowFPS;

		elapsedTime += gameTime::DT;
		FPS++;
		while (elapsedTime >= 1.0f)
		{
			elapsedTime -= 1.0f;
			ShowFPS = FPS;
			FPS = 0;
		}
		std::string tmp = std::to_string(ShowFPS);
		std::string str = "FPS: " + tmp;

		game::GameRender::GetInstance()->DrawText(10, 10, str.c_str(), RGB(0, 0, 0), L"궁서체", 20);

	}


}