#include "FactoryMonster.h"
#include <iostream>
#include "SceneManager.h"
#include "GameRandom.h"
#include "ResourceManager.h"
#include "MCommon.h"
#include "MSoldier.h"
#include "MHero.h"
#include "MKing.h"

FactoryMonster::FactoryMonster() :
    Respontime(10), fixedTime(8), LevelUpTime(15)
    , Second(0), MinMonsterCount(2), MaxMonsterCount(4), BossCount(1), MaxMonsterCountLine(6)
{
    EnemyPercent[0] = 60;
    EnemyPercent[1] = 30;
    EnemyPercent[2] = 10;
    EnemyPercent[3] = 0;
}

FactoryMonster::~FactoryMonster() {}

void FactoryMonster::CreateMonster(EnemyType _type)
{

    game::Object* obj;
    switch (_type)
    {
    case EnemyType::Common:
        obj = new MCommon;        //���� �ӵ�
        obj->transform._position = StartMonsterPosition();
        game::SceneManager::GetInstance()->GetCurScene()->AddObject(obj, game::OBJECT_TYPE::MONSTER);
        break;
    case EnemyType::Soldier:
        obj = new MSoldier;        //���� �ӵ�
        obj->transform._position = StartMonsterPosition();
        game::SceneManager::GetInstance()->GetCurScene()->AddObject(obj, game::OBJECT_TYPE::MONSTER);
        break;
    case EnemyType::Hero:
        obj = new MHero;        //���� �ӵ�
        obj->transform._position = StartMonsterPosition();
        game::SceneManager::GetInstance()->GetCurScene()->AddObject(obj, game::OBJECT_TYPE::MONSTER);
        break;
    case EnemyType::King:
        obj = new MKing;        //���� �ӵ�
        obj->transform._position = StartMonsterPosition();
        game::SceneManager::GetInstance()->GetCurScene()->AddObject(obj, game::OBJECT_TYPE::MONSTER);
        break;
    default:
        //none type Monster
        break;
    }
}

//�ѹ� ������Ʈ�� ������ ���� ���� ���� ����, ������ ������ �������� ������ Ư�� Ʈ���� �� 1ȸ ��ȯ
void FactoryMonster::FixedUpdate()
{
    static int flagBoss;
    fixedTime += FixedUpdateTime;
    Second += FixedUpdateTime;
    if (fixedTime > Respontime)
    {
        int MonsterCount = game::GameRandom::GetIncetance()->RandInt(MaxMonsterCount + 1) + MinMonsterCount;
        for (int i = 0; i < MonsterCount; i++)
        {
            int type = game::GameRandom::GetIncetance()->RandPercent((int)(EnemyType::END), EnemyPercent);
            CreateMonster((EnemyType)type);
        }
        fixedTime -= Respontime;
        flagBoss++;
    }
    if (Second > LevelUpTime)//10�� �� 20���� 40�� ��...
    {
        MinMonsterCount++;
        MaxMonsterCount++;
        if (MaxMonsterCount > MaxMonsterCountLine)
        {
            EnemyPercent[1] += 20;
            EnemyPercent[2] += 10;
            MinMonsterCount -= 3;
            MaxMonsterCount -= 5;
            MaxMonsterCountLine++;
            if(LevelUpTime > 5)
                LevelUpTime--;
            if (Respontime > 5)
                Respontime--;

        }

        Second -= LevelUpTime;
    }
    if (flagBoss == 9)//�� �� ���� ����
    {
        flagBoss = 0;
        game::ResourceManager::GetInstance()->PlayMusic(game::eSoundList::BossBGM, game::eSoundChannel::BGM);
        
        for (int i = 0; i < BossCount; i++)
        {
            CreateMonster(EnemyType::King);
        }
        BossCount++;
    }
}

void FactoryMonster::Update()
{
    Monster::UpdatePlayerPos(game::SceneManager::GetInstance()->GetCurScene()->GetObjectSrc(game::OBJECT_TYPE::PLAYER, "Player"));
}

gameMath::Vector3 FactoryMonster::StartMonsterPosition()
{
    //���� ����
    //X: -300~0 || ScreenWidth~ScreenWidth+300
    //Y: -300~0 || ScreenHeight~ScreenHeight+300
    int X;
    int Y;
    if (game::GameRandom::GetIncetance()->RandInt(2) == 0)
    {
        X = game::GameRandom::GetIncetance()->RandInt(200) - 100;
        if (X > 0)
            X += ScreenWidth;
        Y = game::GameRandom::GetIncetance()->RandInt(ScreenHeight);
    }
    else if (game::GameRandom::GetIncetance()->RandInt(1) == 0)
    {
        Y = game::GameRandom::GetIncetance()->RandInt(200) - 100;
        if (Y > 0)
            Y += ScreenHeight;
        X = game::GameRandom::GetIncetance()->RandInt(ScreenWidth);
    }

    return gameMath::Vector3(X, Y, 0);
}

void FactoryMonster::Render(HDC& _dc) {}

void FactoryMonster::LevelIncrease()
{
    for (int i = 0; i < (int)EnemyType::END; i++)
    {
    }
}
