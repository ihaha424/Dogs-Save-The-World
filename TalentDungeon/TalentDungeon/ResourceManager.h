#pragma once

#ifndef _WIN64
#include "fmod.hpp"
#pragma comment (lib, "fmod_vc.lib")
using namespace FMOD;
#endif
#ifdef _WIN64
#include "fmod.hpp"
#pragma comment (lib, "fmod_vc.lib")
using namespace FMOD;
#endif

#include "LinkedHashMap.hpp"
#include "Define.h"

namespace game
{
	class Texture;

	class ResourceManager
	{
	private:
		static ResourceManager* instance;

		//Texture
		CTN::LinkedHashMap<const char*, Texture*> mapTexture;

		//Sound
		FMOD::System* mSystem;
		FMOD::Channel* mChannel[static_cast<int>(eSoundChannel::End)];
		FMOD::Sound* mSoundList[static_cast<int>(eSoundList::End)];
		float mVolume;

	private:
		ResourceManager();
		~ResourceManager();
	public:
		static ResourceManager* GetInstance();
		static void DestroyResourceManager();

		void Initialize();

		//Texture
		Texture* LoadTexture(const char* strKey, const char* strRelativePath);
		Texture* FindTexture(const char* strKey);

		//Sound
		void LoadMusic(eSoundList list, bool loopcheck, const char* musicPath);
		void PlayMusic(eSoundList list, eSoundChannel channel);
		void StopMusic(eSoundChannel channel);
		void SetVolume(float volume);
	};
}

