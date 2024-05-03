#pragma once
#include <Windows.h>
#include "Define.h"
#include "Scene.h"


namespace game
{
	class SceneManager {
	private:
		static SceneManager* instance;
		Scene* sceneArr[(UINT)SCENE_TYPE::END];
		Scene* curScene;
	public:

	private:
		SceneManager();
		~SceneManager();
	public:
		static SceneManager* GetInstance();
		static void DestroyInstance();

		void FixedUpdate();
		void Update();
		void DestoryUpdate();
		void Render(HDC& _dc);

		void InitSceneManager();
		void ChangeScene(SCENE_TYPE type);
		Scene* GetCurScene();

	};
}