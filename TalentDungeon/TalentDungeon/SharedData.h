#pragma once

class SharedData
{
private:
	static SharedData* instance;

	float SharedDataTime;
	int	KillCount;
	int KillBossCount;
private:
	SharedData();
	~SharedData();
public:
	static SharedData* GetInstance();
	static void DestroyInstance();

	float GetSharedDataTime() {return SharedDataTime;}
	void SetSharedDataTime(float _SharedDataTime) { SharedDataTime = _SharedDataTime; }


	int GetKillCount() { return KillCount; }
	void SetKillCount(int _KillCount) { KillCount = _KillCount; }


	int GetKillBossCount() { return KillBossCount; }
	void SetKillBossCount(int _KillBossCount) { KillBossCount = _KillBossCount; }
};