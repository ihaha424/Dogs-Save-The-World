#include "SceneManager.h"
#include "SceneStage01.h"
#include "SceneStart.h"
#include "SceneWin.h"
#include "SceneLose.h"

namespace game
{
	SceneManager* SceneManager::instance = nullptr;
	SceneManager::SceneManager() : sceneArr{}, curScene(nullptr) {}
	SceneManager::~SceneManager()
	{
		for (UINT i = 0; i < (UINT)SCENE_TYPE::END; i++)
		{
			delete sceneArr[i];
		}
	}

	SceneManager* SceneManager::GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new SceneManager();
		}
		return instance;
	}

	void SceneManager::DestroyInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void SceneManager::InitSceneManager()
	{
		//Scene생성
		
		sceneArr[(UINT)SCENE_TYPE::START] = new SceneStart;
		sceneArr[(UINT)SCENE_TYPE::STAGE_01] = new SceneStage01;
		sceneArr[(UINT)SCENE_TYPE::FINISH_WIN] = new SceneWin;
		sceneArr[(UINT)SCENE_TYPE::FINISH_LOSE] = new SceneLose;

		//현재 씬 설정
		curScene = sceneArr[(UINT)SCENE_TYPE::START];
		curScene->Enter();
	}

	void SceneManager::ChangeScene(SCENE_TYPE type)
	{
		curScene->Exit();
		curScene = sceneArr[(UINT)type];
		curScene->Enter();
	}

	Scene* SceneManager::GetCurScene()
	{
		return curScene;
	}

	void SceneManager::FixedUpdate()
	{
		curScene->FixedUpdate();
	}

	void SceneManager::Update()
	{
		curScene->Update();
	}

	void SceneManager::DestoryUpdate()
	{
		curScene->DestoryUpdate();
	}

	void SceneManager::Render(HDC& _dc)
	{
		curScene->Render(_dc);
	}

}