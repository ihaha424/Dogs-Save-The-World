#include "ResourceManager.h"
#include "PathManager.h"
#include "Texture.h"

namespace game
{
	ResourceManager* ResourceManager::instance = nullptr;
	ResourceManager::ResourceManager(): 
		//Sound
		mSystem(), mChannel{}, mSoundList{}, mVolume(0.5f) {}
	ResourceManager::~ResourceManager()
	{
		//Texture
		CTN::LinkedHashMap<const char*, Texture*>::Iterator iter(&(mapTexture.list), mapTexture.capacity);
		while (!iter.IsEnd())
		{
			CTN::LinkedHashMap<const char*, Texture*>::Data* data = iter.GetCurrent();
			if (data != nullptr)
			{
				if(data->value != nullptr)
					delete data->value;
				if (data->key != nullptr)
					delete[] (data->key);
			}
			iter.Next();
		}

		//Sound
		mSystem->release();
		mSystem->close();
	}

	ResourceManager* ResourceManager::GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new ResourceManager();
		}
		return instance;
	}

	void ResourceManager::DestroyResourceManager()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void ResourceManager::Initialize()
	{
		LoadMusic(eSoundList::StartBGM, true, "Resource\\Sound\\StartBGM.wav");
		LoadMusic(eSoundList::MainBGM, true, "Resource\\Sound\\MainBGM.mp3");
		LoadMusic(eSoundList::BossBGM, true, "Resource\\Sound\\BossBGM.mp3");
		
		LoadMusic(eSoundList::DashEffect, false, "Resource\\Sound\\DashEffect.mp3");
		LoadMusic(eSoundList::ShotEffect, false, "Resource\\Sound\\ShotEffect.mp3");
		LoadMusic(eSoundList::CollisionEffect, false, "Resource\\Sound\\CollisionEffect.mp3");

		
		SetVolume(0.5f); //크기조정
	}


	/*

	//	Texture

	*/

	//안나오면 Resize를 통해 제대로 형식을 맞추어야 한다.(다운 받은 파일은 손상이되어서 로드가 안될가능성이 매우큼)
	Texture* ResourceManager::LoadTexture(const char* strKey, const char* strRelativePath)
	{
		Texture* tex = FindTexture(strKey);
		if (tex != nullptr)
			return tex;

		PathManager* manager = PathManager::GetInstance();
		tex = new Texture;
		const char* tmep = manager->GetResourcePath();
		char* playerTexPath = manager->Strjoin(tmep, strRelativePath);
		tex->Load(playerTexPath);
		free(playerTexPath);

		tex->SetKey(strKey);
		tex->SetPath(strRelativePath);
		mapTexture.Put(strKey, tex);
		return tex;
	}

	Texture* ResourceManager::FindTexture(const char* strKey)
	{
		return mapTexture.Get(strKey);
	}



	/*
	
	//	Sound

	*/

	void ResourceManager::LoadMusic(eSoundList list, bool loopcheck, const char* musicPath)
	{
		PathManager* manager = PathManager::GetInstance();
		const char* tmep = manager->GetResourcePath();
		char* playerSoundPath = manager->Strjoin(tmep, musicPath);

		System_Create(&mSystem);
		mSystem->init((int)eSoundChannel::End, FMOD_INIT_NORMAL, 0);

		if (loopcheck)
			mSystem->createSound(musicPath, FMOD_LOOP_NORMAL, 0, &mSoundList[static_cast<int>(list)]);
		else
			mSystem->createSound(musicPath, FMOD_LOOP_OFF, 0, &mSoundList[static_cast<int>(list)]);

		delete playerSoundPath;
	}
	void ResourceManager::PlayMusic(eSoundList list, eSoundChannel channel)
	{
		mChannel[static_cast<int>(channel)]->stop();
		mSystem->playSound(mSoundList[static_cast<int>(list)], NULL, 0, &mChannel[static_cast<int>(channel)]);
		mChannel[static_cast<int>(channel)]->setVolume(mVolume);
	}
	void ResourceManager::StopMusic(eSoundChannel channel)
	{
		mChannel[static_cast<int>(channel)]->stop();
	}
	void ResourceManager::SetVolume(float volume)
	{
		mVolume = volume;
		for (unsigned int i = 0; i < static_cast<unsigned int>(eSoundChannel::End); ++i)
			mChannel[i]->setVolume(mVolume);
	}
}
