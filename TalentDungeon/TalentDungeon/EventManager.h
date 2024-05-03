#pragma once
#include "Button.h"


class Player;

class EventManager :
    public game::Button
{
private:
    static int KillMonster;
    int LevelUpTriggrr;
    int Onflag;
    int ShowIndex[2];
    int MaxSkill[5];
    float Exp;
    Player* player;

public:
    EventManager();
    ~EventManager();

    void SetLevelUpUI();
    void SetPlayer(Player* _player) { player = _player; }
    void EffectLevelUp(int index);


    virtual void FixedUpdate();
    virtual void Update();
    virtual void Render(HDC& _dc);


    static void UpKillMonsterCount(int i = 1) { KillMonster += i; }
};

