#include "SharedData.h"

SharedData* SharedData::instance = nullptr;
SharedData::SharedData(): SharedDataTime(0), KillCount(0), KillBossCount(0) {}
SharedData::~SharedData() {}
SharedData* SharedData::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new SharedData();
	}
	return instance;
}

void SharedData::DestroyInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}